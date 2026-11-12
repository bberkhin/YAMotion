/*
 * gcmc_alloc.h - run-scoped resources for the embedded gcmc compiler
 *
 * Included at the end of config.h (and by grammary.y). It redirects the CRT calls that
 * need per-run bookkeeping to the implementations in gcmc_api.c:
 *  - malloc/realloc/free/strdup/...  -> private heap that is destroyed when a run ends
 *  - fopen/fclose/access            -> relative names resolved against the run's work dir,
 *                                      forgotten files are closed when a run ends
 *  - exit                           -> longjmp back to gcmc_run() (no process exit)
 *  - stderr                         -> per-run log stream delivered to the caller
 */
#ifndef GCMC_ALLOC_H
#define GCMC_ALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <io.h>
#include <malloc.h>

#ifdef __cplusplus
extern "C" {
#endif

void *gcmc_malloc(size_t n);
void *gcmc_calloc(size_t n, size_t sz);
void *gcmc_realloc(void *p, size_t n);
void gcmc_free(void *p);
char *gcmc_strdup(const char *s);
wchar_t *gcmc_wcsdup(const wchar_t *s);

FILE *gcmc_fopen(const char *name, const char *mode);
int gcmc_fclose(FILE *fp);
int gcmc_access(const char *name, int mode);

__declspec(noreturn) void gcmc_exit(int code);
FILE *gcmc_errfp(void);
void gcmc_check_cancel(void);

#ifdef __cplusplus
}
#endif

#undef malloc
#undef calloc
#undef realloc
#undef free
#undef strdup
#undef _strdup
#undef wcsdup
#undef _wcsdup
#undef fopen
#undef fclose
#undef access
#undef exit
#undef stderr

#define malloc(n)		gcmc_malloc(n)
#define calloc(n, s)		gcmc_calloc(n, s)
#define realloc(p, n)		gcmc_realloc(p, n)
#define free(p)			gcmc_free(p)
#define strdup(s)		gcmc_strdup(s)
#define _strdup(s)		gcmc_strdup(s)
#define wcsdup(s)		gcmc_wcsdup(s)
#define _wcsdup(s)		gcmc_wcsdup(s)
#define fopen(n, m)		gcmc_fopen(n, m)
#define fclose(f)		gcmc_fclose(f)
#define access(n, m)		gcmc_access(n, m)
#define exit(c)			gcmc_exit(c)
#define stderr			gcmc_errfp()

#endif /* GCMC_ALLOC_H */
