#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <thread>


using namespace std;

struct sock_data{
	int sockfd;
	struct sockaddr_in clientAddress;
	int numClient;
	char cmd;	
};

class TCPServer {
	public:
		int start(int port);
		void stop();
		//char cmd;
		sock_data data;

	private:
		//int sockfd;
		struct sockaddr_in serverAddress;
		//struct sockaddr_in clientAddress;
		//static int numClient;
		static void * connectionHandler_(void * arg);
};

#endif