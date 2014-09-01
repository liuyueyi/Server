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
#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#define filename "file.d"
#define temp_pathname "temp2.d"

void cls_receive(int sockfd)
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
		printf("%s", buffer);
		fprintf(f, "%s", buffer);
	}
	fclose(f);
}


void cls_send(int sockfd)
{
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
}


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
	
	int choose = -1;
	printf("receive 0, send 1\n");
	do{
		scanf("%d", &choose);
	}while(choose != 0 && choose != 1);
	
	char com[2]; 
	sprintf(com, "%d", choose);
	send(sockfd, com, strlen(com), 0);
	
		
	switch(choose)
	{
		case 0:
			cls_send(sockfd);
			break;
		case 1:
			cls_receive(sockfd);
			break;
	}
	
	
	printf("-----------send over------------\n");
	close(sockfd);
	return 0;
}
