/*
 * gcmc_api.c - runs the gcmc compiler inside the calling process.
 *
 * This file is deliberately NOT built with gcmc_alloc.h: it provides the real
 * implementations behind the wrappers declared there.
 */
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <process.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>

#include "gcmc_api.h"

int gcmc_main(int argc, char *argv[]);	/* gcmc.c */

#define GCMC_STACK_SIZE		(32 * 1024 * 1024)
#define GCMC_MAX_OPEN_FILES	64

/* ---- per run, per thread state ---- */
static __declspec(thread) HANDLE	t_heap;
static __declspec(thread) jmp_buf	t_jmp;
static __declspec(thread) int		t_jmp_valid;
static __declspec(thread) int		t_exitcode;
static __declspec(thread) FILE		*t_errfp;
static __declspec(thread) char		t_workdir[MAX_PATH];
static __declspec(thread) FILE		*t_files[GCMC_MAX_OPEN_FILES];
static __declspec(thread) volatile long	*t_cancel;

/* ---- allocation: private heap, destroyed in one go at the end of a run ---- */
void *gcmc_malloc(size_t n)
{
	return t_heap ? HeapAlloc(t_heap, 0, n ? n : 1) : malloc(n);
}

void *gcmc_calloc(size_t n, size_t sz)
{
	return t_heap ? HeapAlloc(t_heap, HEAP_ZERO_MEMORY, (n * sz) ? n * sz : 1) : calloc(n, sz);
}

void *gcmc_realloc(void *p, size_t n)
{
	if(!t_heap)
		return realloc(p, n);
	if(!p)
		return HeapAlloc(t_heap, 0, n ? n : 1);
	return HeapReAlloc(t_heap, 0, p, n ? n : 1);
}

void gcmc_free(void *p)
{
	if(!p)
		return;
	if(t_heap)
		HeapFree(t_heap, 0, p);
	else
		free(p);
}

char *gcmc_strdup(const char *s)
{
	size_t n = strlen(s) + 1;
	char *p = (char *)gcmc_malloc(n);
	if(p)
		memcpy(p, s, n);
	return p;
}

wchar_t *gcmc_wcsdup(const wchar_t *s)
{
	size_t n = (wcslen(s) + 1) * sizeof(wchar_t);
	wchar_t *p = (wchar_t *)gcmc_malloc(n);
	if(p)
		memcpy(p, s, n);
	return p;
}

/* ---- files ---- */
static const char *resolve(const char *name, char *buf, size_t nbuf)
{
	if(!t_workdir[0] || !name)
		return name;
	/* absolute: drive letter, UNC or rooted path */
	if(name[0] == '/' || name[0] == '\\' || (name[0] && name[1] == ':'))
		return name;
	_snprintf(buf, nbuf, "%s\\%s", t_workdir, name);
	buf[nbuf - 1] = 0;
	return buf;
}

FILE *gcmc_fopen(const char *name, const char *mode)
{
	char buf[MAX_PATH * 2];
	FILE *fp = fopen(resolve(name, buf, sizeof(buf)), mode);
	if(fp) {
		int i;
		for(i = 0; i < GCMC_MAX_OPEN_FILES; i++) {
			if(!t_files[i]) {
				t_files[i] = fp;
				break;
			}
		}
	}
	return fp;
}

int gcmc_fclose(FILE *fp)
{
	int i;
	for(i = 0; i < GCMC_MAX_OPEN_FILES; i++) {
		if(t_files[i] == fp)
			t_files[i] = NULL;
	}
	return fclose(fp);
}

int gcmc_access(const char *name, int mode)
{
	char buf[MAX_PATH * 2];
	return _access(resolve(name, buf, sizeof(buf)), mode);
}

/* ---- exit and error stream ---- */
__declspec(noreturn) void gcmc_exit(int code)
{
	if(t_jmp_valid) {
		t_exitcode = code;
		longjmp(t_jmp, 1);
	}
	exit(code);
}

FILE *gcmc_errfp(void)
{
	return t_errfp ? t_errfp : stderr;
}

void gcmc_check_cancel(void)
{
	if(t_cancel && *t_cancel)
		gcmc_exit(2);
}

/* ---- the run ---- */
typedef struct run_s {
	int			argc;
	char			**argv;
	const gcmc_params_t	*params;
	HANDLE			errwrite;	/* write end of the log pipe or NULL */
	int			rc;
} run_t;

static unsigned __stdcall run_thread(void *arg)
{
	run_t *r = (run_t *)arg;
	const gcmc_params_t *p = r->params;
	int i;

	t_heap = HeapCreate(HEAP_NO_SERIALIZE, 0, 0);
	t_cancel = p ? p->cancel : NULL;
	t_workdir[0] = 0;
	if(p && p->workdir && p->workdir[0]) {
		strncpy(t_workdir, p->workdir, sizeof(t_workdir) - 1);
		t_workdir[sizeof(t_workdir) - 1] = 0;
	}
	if(r->errwrite) {
		int fd = _open_osfhandle((intptr_t)r->errwrite, _O_BINARY);
		if(fd >= 0) {
			t_errfp = _fdopen(fd, "wb");
			if(t_errfp)
				setvbuf(t_errfp, NULL, _IONBF, 0);	/* every message goes out at once */
			else
				_close(fd);
		}
	}

	if(!t_heap) {
		r->rc = 1;
	} else {
		t_jmp_valid = 1;
		if(!setjmp(t_jmp))
			r->rc = gcmc_main(r->argc, r->argv);
		else
			r->rc = t_exitcode;
		t_jmp_valid = 0;

		/* Close what the run forgot (error exits) */
		for(i = 0; i < GCMC_MAX_OPEN_FILES; i++) {
			if(t_files[i]) {
				fclose(t_files[i]);
				t_files[i] = NULL;
			}
		}
		HeapDestroy(t_heap);
		t_heap = NULL;
	}

	/* Closing the stream closes the pipe's write end: the reader sees the end of the log */
	if(t_errfp) {
		fclose(t_errfp);
		t_errfp = NULL;
	}
	return 0;
}

/* Reads the log pipe while the run is going and hands out complete lines to the callback */
static void pump_log(HANDLE rd, HANDLE th, const gcmc_params_t *p)
{
	char *acc = NULL;	/* not yet delivered: incomplete last line */
	size_t nacc = 0, cap = 0;
	int finished = 0;

	for(;;) {
		DWORD avail = 0;
		if(!PeekNamedPipe(rd, NULL, 0, NULL, &avail, NULL))
			break;	/* broken: write end closed and everything consumed */
		if(avail) {
			char buf[4096];
			DWORD got = 0;
			if(!ReadFile(rd, buf, sizeof(buf), &got, NULL) || !got)
				break;
			if(nacc + got + 1 > cap) {
				cap = (nacc + got + 1) * 2;
				acc = (char *)realloc(acc, cap);
				if(!acc)
					return;
			}
			memcpy(acc + nacc, buf, got);
			nacc += got;
			/* deliver up to the last newline */
			{
				size_t k = nacc;
				while(k > 0 && acc[k - 1] != '\n')
					k--;
				if(k > 0) {
					char save = acc[k];
					acc[k] = 0;
					p->log(acc, p->log_user);
					acc[k] = save;
					memmove(acc, acc + k, nacc - k);
					nacc -= k;
				}
			}
			continue;
		}
		if(finished)
			break;
		if(WaitForSingleObject(th, 10) == WAIT_OBJECT_0)
			finished = 1;	/* one more pass to drain what is left */
	}
	if(nacc) {
		acc[nacc] = 0;
		p->log(acc, p->log_user);
	}
	free(acc);
}

int gcmc_run(int argc, char **argv, const gcmc_params_t *params)
{
	run_t r;
	HANDLE th;
	HANDLE rd = NULL;

	r.argc = argc;
	r.argv = argv;
	r.params = params;
	r.errwrite = NULL;
	r.rc = 1;

	if(params && params->log) {
		if(!CreatePipe(&rd, &r.errwrite, NULL, 1 << 16))
			rd = r.errwrite = NULL;
	}

	th = (HANDLE)_beginthreadex(NULL, GCMC_STACK_SIZE, run_thread, &r, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
	if(!th) {
		if(rd) {
			CloseHandle(rd);
			CloseHandle(r.errwrite);
		}
		return 1;
	}
	if(rd)
		pump_log(rd, th, params);
	WaitForSingleObject(th, INFINITE);
	CloseHandle(th);
	if(rd)
		CloseHandle(rd);
	return r.rc;
}
