#include "common.h" 
#include "tcpserver.h" 

///////////////////////////////////////////////////////////////////////////////////////////////////////
void * TCPServer::connectionHandler_(void * arg)
{
    bool flag = true;
    int newSocketID;

    struct sock_data *sockData = (struct sock_data*)arg;
	pthread_detach(pthread_self());

    while(flag){
        if(sockData->numClient == 0){
            socklen_t clientLen = sizeof(sockData->clientAddress);
            newSocketID = accept(sockData->sockfd, (struct sockaddr *)&sockData->clientAddress, &clientLen);
            if(newSocketID < 0){
                cerr << "ERROR: connection cannot be accepted error:" << newSocketID << endl;
            } else {
                sockData->numClient++;
            }
        }

        if(sockData->numClient > 0){
            int n = recv(newSocketID, &sockData->cmd, sizeof(sockData->cmd), MSG_WAITALL);
            if (n <= 0) {
                cerr << "ERROR: cannot read the data!" << endl;
                close(newSocketID);
                sockData->numClient = 0;
            }
            DEBUG_PRINT("Received data: %c\n", sockData->cmd);
            if(sockData->cmd == 'q'){
                flag = false;
            }
        }
    }

    close(newSocketID);
    close(sockData->sockfd);

    DEBUG_PRINT("server disconnected\n");
   	pthread_exit(NULL);
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
int TCPServer::start(int port)
{
    int ret = 0;

    data.sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(data.sockfd < 0){
        cerr << "ERROR: socket cannot be created!" << endl;
        return -1;
    }
 	memset(&serverAddress,0,sizeof(serverAddress));
	serverAddress.sin_family      = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port        = htons(port);

    char *ip = inet_ntoa(serverAddress.sin_addr);
    DEBUG_PRINT("IP Address: %s\n", ip);
        std::cout << "IP Address: " << ip << std::endl;


    int optval = 1;
	ret = setsockopt(data.sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    ret = setsockopt(data.sockfd, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));
    if (ret < 0) {
        cerr << "ERROR: set socket options!" << endl;
        close(data.sockfd);
        return -1;
    }

	if( bind(data.sockfd,(struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
        close(data.sockfd);
        cerr << "ERROR: bind socket!" << endl;
		return -1;
	}

    if(listen(data.sockfd, 1) < 0){
        close(data.sockfd);
        cerr << "ERROR: listen port!" << endl;
		return -1;
	}

    data.numClient = 0;
    pthread_t threadID;
    /*
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    */
    //ret = pthread_create(&threadID, &attr, connectionHandler, NULL);
    ret = pthread_create(&threadID, NULL, connectionHandler_, (void *)&data);
    if(ret < 0){
        close(data.sockfd);
        cerr << "ERROR: connectionHandler cannot be created!" << endl;
		return -1;
	}


	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void TCPServer::stop() 
{
	close(data.sockfd);
}