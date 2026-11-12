/*
 * gcmc_api.h - embedding interface of the G-code meta compiler
 *
 * gcmc_run() does exactly what "gcmc_vc.exe <args>" does, but inside the calling process:
 * the compiler runs in its own thread with private (thread-local) state and a private
 * heap, so any number of runs can follow each other and nothing leaks between them.
 */
#ifndef GCMC_API_H
#define GCMC_API_H

#ifdef __cplusplus
extern "C" {
#endif

/* Receives everything the compiler writes to its error stream (errors, warnings, message(), ...)
 * while it runs: complete lines, each call may carry several. It is called on the thread that called gcmc_run(). */
typedef void (*gcmc_log_fn)(const char *text, void *user);

typedef struct gcmc_params {
	const char	*workdir;	/* Relative file names (source, -o, include(), ...) are resolved against it.
					   NULL = process current directory. */
	gcmc_log_fn	log;		/* NULL = write to the process' stderr */
	void		*log_user;
	volatile long	*cancel;	/* Optional. Set to non-zero from another thread to abort the run */
} gcmc_params_t;

/* argv[0] is the program name as in main(). Returns the exit code ("process" exit status). */
int gcmc_run(int argc, char **argv, const gcmc_params_t *params);

#ifdef __cplusplus
}
#endif

#endif /* GCMC_API_H */
