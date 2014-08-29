/*
 * client.c
 *
 *  Created on: 2014-8-29
 *      Author: wzb
 */
 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#define filename "file.d"

int main()
{
	int sockfd;
	struct sockaddr_in server_addr;
	uint16_t port = 10033;
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "socket eerror\n");
		exit(1);
	}
	
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");;
	
	if(connect(sockfd, (struct sockaddr*)(&server_addr), sizeof(struct sockaddr))<0)
	{
		fprintf(stderr, "connect eerror\n");
		return -1;
	}	
	
	FILE *f = NULL;
	if((f = fopen(filename, "r")) == NULL)
	{
		fprintf(stderr, "%s file error\n", filename);
		close(sockfd);
		exit(1);
	}
	
	char buf[LINE_MAX];
	while(fgets(buf, LINE_MAX, f))
	{
		send(sockfd, buf, strlen(buf), 0);
	}
	fclose(f);
	printf("-----------send over------------\n");
	close(sockfd);
	return 0;
}
