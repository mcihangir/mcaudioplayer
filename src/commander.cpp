////////////////////////////////////////////////////////////
//
// TCP Server with SFML - Simple and Fast Multimedia Library
// 2024 Mehmet Cihangir (mehmet.cihangir@yahoo.com)
//
////////////////////////////////////////////////////////////
#include "common.h" 
#include "commander.h" 
     
///////////////////////////////////////////////////////////////////////////////////////////////////////
void * Commander::connectionHandler(void * arg)
{
    bool flag = true;

    struct commander_data *sockData = (struct commander_data*)arg;
	pthread_detach(pthread_self());

    while(flag){
        if(sockData->numClient == 0){
            cout << "Waiting for a connection..." << endl;
            if( sockData->listener.accept(sockData->socket) != sf::Socket::Done ){
                cerr << "ERROR: connection cannot be accepted" << endl;
            } else {
                sockData->numClient++;
            }
        }

        if(sockData->numClient > 0){
            std::size_t recSize;
            //char dt;
            if (sockData->socket.receive(&sockData->cmd, sizeof(sockData->cmd), recSize) == sf::Socket::Done){
            //if (sockData->socket.receive(&dt, sizeof(sockData->cmd), recSize) == sf::Socket::Done){
                DEBUG_PRINT("Received data: %c\n", sockData->cmd);
                if(sockData->cmd == 'q'){
                    flag = false;
                }
            }else {
                if(recSize == 0){
                    DEBUG_PRINT("socket is closed!\n");
                }else {
                    cerr << "ERROR: cannot read the data!" << endl;
                }
                sockData->socket.disconnect();
                sockData->numClient = 0;
            }
        }
    }

    sockData->socket.disconnect();
    sockData->listener.close();

    DEBUG_PRINT("server disconnected\n");
   	pthread_exit(NULL);
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
int Commander::start(int port)
{
    if( port<0 || port > 65535){
        cerr << "ERROR: wrong port number!" << endl;
        return -1;
    }
    //bind a listener to the port
    if(data.listener.listen(port) != sf::Socket::Done){
        cerr << "ERROR: listener cannot be started" << endl;
        return -1;
    }
    data.numClient = 0;
    data.cmd = ' ';
    pthread_t threadID;
    if(pthread_create(&threadID, NULL, connectionHandler, (void *)&data) < 0){
        data.listener.close();
        cerr << "ERROR: connectionHandler cannot be created!" << endl;
		return -1;
	}
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void Commander::stop() 
{
    data.listener.close();
}