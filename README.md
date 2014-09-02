Server
======

  a tcp server by c
  this server can used as a background process, the server is used to receive text file and the client used to send text file by tcp.
  

Install
=======
under terminal:
  make


Test Command
============
  you can either use init.sh to start/stop/restart the server, or directly input ./kmd under terminal to start the server.The kmd.pid file saved the process pid of the server, so if you want to kill the server process, except use init.sh script, you can also directly input(kill -9 `cat kmd.pid`) to kill the server
  
  for example:
    start server:  ./init.sh start
    
    start client: ./client
    
    kill server: ./init.sh kill
    restart server: ./init.sh restart

  after the input command, you will find that there is a new file(temp.d), if there is no error, the content in file temp.d should be the same as the content in file.d

Source Code Analysis
====================
server.c/server.h
-----------------
  this source code implements a tcp server, it include create a socket and bind it to 10033 port(you can also choose another port), then listener the request from other computer throw the Intenert. When there is a valid request, then the main process will create a child process and  go into server_process() to respose the request.
  In this project, the server not only implements receive text file from other and save it in local disk, but alos include send file to client. The two method was called by client's request. After respose the client request, this child process will be killed!

kmd.c
-----
  This source code contain main function, it's used to create a background process and save the process pid into file kmd.pid. In the code, I use getopt_long to decode the command input parameters. If you want to get more about this function, you can google how to use it. Here(http://my.oschina.net/u/566591/blog/307892) I had summaried the useage of daemon
  This file also implements terminal interactive interface, you can get how to use this command by (./kmd -h or ./kmd --help).
  You can choose the save file pathname by set config_pathname(./kmd -c xxx/tmp.conf or ./init.sh start -c xxx/tmp.conf), the receive file's pathname will append ".tm" to the original config pathname.
  Use -p to set listen port, -i to set accepted ip, -P to set rsa verify public key pathname and -S to set rsa sign private key pathname.
  
client.c
--------
  This source code implements a simple tcp client, it can connect the remote tcp server, first to send requset to choose receive file from server or send file to server. Pay attention to the code blow. If server buffer size is bigger then 1, the receive file will smaller then expected.
  
  	client:
	char com[2]; 
	sprintf(com, "%d", choose);
	send(sockfd, com, strlen(com), 0);
	
	server:
	char buffer[1];
  	data_len = recv(sockfd, buffer, 1, 0); 
  	if(data_len < 0)
  	{
  		fprintf(stderr, "receive error\n");
  		exit(1);
  	}
  	int command = atoi(buffer);
	
  
init.sh
-------
  Shell Script, used to control the server. Read "Test Command" to get more use
  You should replace the path "/home/pc/workspace/daemon/Server/kmd" to yours

Makefile
--------
  makefile use to compile and generate the executable progress
