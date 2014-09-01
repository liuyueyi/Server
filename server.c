/*
 * server.c
 *
 *  Created on: 2014-8-29
 *      Author: wzb
 */
 
#include "server.h"

#define temp_pathname "temp.d"

bool verify_client(int sockfd)
{
	char buffer[20];
	int len = 0;
	memset(buffer, 0, sizeof(buffer));
	
	srand((int)time(0));
	int n = rand() % 1000;
	sprintf(buffer, "%d", n);
	
	if(send(sockfd, buffer, strlen(buffer), 0) != strlen(buffer))
		return false;
	
	if((len = recv(sockfd, buffer, 20, 0)) < 0)
		return false;
	int m = atoi(buffer);
	if(m == n)
		return true;
	else
		return false;
}


void receive_volume_key(int sockfd)
{
	char buffer[1024];
	int data_len;
	FILE *f;
	if((f = fopen(temp_pathname, "w")) == NULL)
	{
		fprintf(stderr, "crete temp file %s error\n", temp_pathname);
		exit(1);
	}
	
	while((data_len = recv(sockfd, buffer, 1024, 0)) >0)
	{
		if(data_len < 1024)
			buffer[data_len] = '\0';
		fprintf(f, "%s", buffer);
	}
	fclose(f);
}


void send_volume_key(int sockfd)
{
	char buffer[LINE_MAX];
	FILE *f;
	if((f = fopen("file.d", "r")) == NULL)
	{
		fprintf(stderr, "volume key pathname %s error\n", temp_pathname);
		exit(1);
	}
	
	while(fgets(buffer, LINE_MAX, f))
		send(sockfd, buffer, strlen(buffer), 0);
		
	fclose(f);	
}


void server_process(int sockfd)
{
	int data_len = 0;
	char buffer[1];
	// receive and judge the client request
	data_len = recv(sockfd, buffer, 1, 0); 
	if(data_len < 0)
	{
		fprintf(stderr, "receive error\n");
		exit(1);
	}
	int command = atoi(buffer);
	
	switch(command)
	{
		case 0: // receive file
			receive_volume_key(sockfd);
			break;
		case 1: // send file
			send_volume_key(sockfd);
			break;
		default:
			exit(1);
	}
}


void init_server(const struct kmd_option *x)
{
	int sockfd;
	int clientfd;
	uint16_t port = x->port;
	
	struct sockaddr_in server_addr, client_addr;
	bzero(&server_addr, sizeof(server_addr));
	if(strlen(x->ip) == 0)
		server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr  = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "open data stream socket failed!\n");
		exit(1);
	}
	
	if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		fprintf(stderr, "bind data socket failed!\n");
		exit(1);
	}
	
	if(listen(sockfd, SOMAXCONN) < 0)
	{
		fprintf(stderr, "listen data stream failed\n");
		exit(1);
	}
	
	while(1)
	{
		socklen_t len = sizeof(client_addr);
		clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &len);
		if(clientfd < 0)
		{
			fprintf(stderr, "accept error\n");
			continue;
		}
		
		int pid = fork();
		if(pid == 0)
		{
			server_process(clientfd);
			exit(0);
		}
		close(clientfd);
	}
}
