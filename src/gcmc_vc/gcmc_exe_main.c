/* Command-line front end: gcmc_vc.exe is a thin wrapper around the embedded compiler */
#include <string.h>
#include "gcmc_api.h"

int main(int argc, char *argv[])
{
	gcmc_params_t p;
	memset(&p, 0, sizeof(p));
	return gcmc_run(argc, argv, &p);
}
