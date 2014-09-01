#include "server.h"
#include <getopt.h>
#define pid_pathname "kmd.pid"

struct option const long_options[] =
{
{ "ip", required_argument, NULL, 'i' },
{ "port", required_argument, NULL, 'p' },
{ "config_pathname", required_argument, NULL, 'c' },
{ "sk_pathname", required_argument, NULL, 'S' },
{ "pk_pathname", required_argument, NULL, 'P' },
{ "help", no_argument, NULL, 'h' },
{ NULL, 0, NULL, 0 } };

void kmd_option_init(struct kmd_option *x)
{
	x->port = DEFAULT_PORT;
	strcpy(x->ip, "");
	strcpy(x->sk_pathname, SK_FILENAME);
	strcpy(x->pk_pathname, PK_FILENAME);
	strcpy(x->config_pathname, CONFIG_FILENAME);
}


void decode_switch(int argc, char **argv, struct kmd_option *x)
{
	int c;
	while (1)
	{
		c = getopt_long_only(argc, argv, "i:p:C:P:S:", long_options, NULL );
		if (c == -1)
			break;

		switch (c)
		{
		case 'i':
			if (*optarg == '=')
				++optarg;
			if (optarg && strlen(optarg) < PATH_MAX)
				strcpy(x->ip, optarg);
			break;

		case 'p':
			if (*optarg == '=')
				++optarg;
			if (optarg && strlen(optarg) < 10)
				x->port = atoi(optarg);
			break;

		case 'c':
			if (*optarg == '=')
				++optarg;
			if (strlen(optarg) < PATH_MAX)
				strcpy(x->config_pathname, optarg);
			break;

		case 'P':
			if (*optarg == '=')
				++optarg;
			if (strlen(optarg) < PATH_MAX)
				strcpy(x->pk_pathname, optarg);
			break;
		case 'S':
			if (*optarg == '=')
				++optarg;
			if (strlen(optarg) < PATH_MAX)
				strcpy(x->sk_pathname, optarg);
			break;

		case 'h':
			// help();
			break;
		case '?':
			break;

		default:
			printf("?? getopt returned character code 0%o ??\n", c);
			exit(-1);
		}
	}
}


int main(int argc, char **argv)
{
	struct kmd_option *x = (struct kmd_option *) malloc(
			sizeof(struct kmd_option));;
	kmd_option_init(x);
	decode_switch(argc, argv, x);
	
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
	init_server(x);
	return 0;
}
