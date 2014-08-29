#include "server.h"
#define pid_pathname "kmd.pid"

int main(int argc, char **argv)
{
	FILE * pf = NULL;
	if (NULL == (pf = fopen(pid_pathname, "w")))
	{
		fprintf(stderr, "create %s file error\n", pid_pathname);
		exit(1);
	}

	if(daemon(1, 0) < 0)
	{
		fprintf(stderr, "start service, error\n");
		exit(1);
	}

	// record the process pid
	fprintf(pf, "%d", getpid());
	fclose(pf);
	init_server();
	return 0;
}
