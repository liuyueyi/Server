/*
 * server.c
 *
 *  Created on: 2014-8-29
 *      Author: wzb
 */
 
#include "server.h"

#define temp_pathname "temp.d"
void server_process(int sockfd)
{
	char buffer[1024];
	int data_len = 0;
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

void init_server()
{
	int sockfd;
	int clientfd;
	uint16_t port = 10033;
	
	struct sockaddr_in server_addr, client_addr;
	bzero(&server_addr, sizeof(server_addr));
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
