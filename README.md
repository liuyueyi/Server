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
  In this project, the server only implements receive text file from other and save it in local disk. If receive all the content, then this child process will be killed!

kmd.c
-----
  This source code contain main function, it's used to create a background process and save the process pid into file kmd.pid
  
client.c
--------
  This source code implements a simple tcp client, it has only one function, just connect the server and send file to it.
  
init.sh
-------
  Shell Script, used to control the server. Read "Test Command" to get more use

Makefile
--------
  makefile use to compile and generate the executable progress
