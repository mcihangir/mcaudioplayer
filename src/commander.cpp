////////////////////////////////////////////////////////////
//
// TCP Server & Audio Player with SFML - Simple and Fast Multimedia Library
// 2024 Mehmet Cihangir (mehmet.cihangir@yahoo.com)
//
////////////////////////////////////////////////////////////
#include "common.h" 
#include "commander.h" 
     
///////////////////////////////////////////////////////////////////////////////////////////////////////
void * Commander::connectionHandler(void * arg)
{
    bool flag = true;
    struct commander_data *dt = (struct commander_data*)arg;
    dt->isOnline = true;
	pthread_detach(pthread_self());

    while(flag){
        if(dt->numClient == 0){
            DEBUG_PRINT("Waiting for a connection...\n");
            if( dt->listener.accept(dt->socket) == sf::Socket::Done ){
                dt->numClient++;
            } else {
                cerr << "ERROR: connection cannot be accepted" << endl;
            }
        }

        if(dt->numClient > 0){
            std::size_t recSize;
            if (dt->socket.receive(&dt->cmd, sizeof(dt->cmd), recSize) == sf::Socket::Done){
                DEBUG_PRINT("Received data: %c\n", dt->cmd);
                switch(dt->cmd){
                    case 'p':
                        dt->sound.play();
                        dt->cmd = '\0';
                    break;
                    case 's':
                        dt->sound.stop();
                        //dt->sound.pause();
                        dt->cmd = '\0';
                    break;
                    case 'q':
                        flag = false;
                    break;
                    default:
                    break;
                }
            }else {
                if(recSize == 0){
                    DEBUG_PRINT("Socket is closed!\n");
                }else {
                    cerr << "ERROR: cannot read the data!" << endl;
                }
                dt->socket.disconnect();
                dt->numClient = 0;
            }
        }
    }
              
   	pthread_exit(NULL);
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
int Commander::start(char* file, int port)
{
    data.isOnline = false;
    if( port < 0 || port > 65535){
        cerr << "ERROR: wrong port number!" << endl;
        return -1;
    }
    if (!data.buffer.loadFromFile(file)) {
        cerr << "ERROR: Usage: ./mcaudioplayer auido_file [TCP port]" << endl;
        cerr << "ERROR: Please enter the path of the audio file like /home/mypc/sound.wav" << endl;
        return -1;
    }
    data.sound.setBuffer(data.buffer);
    //bind a listener to the port
    if(data.listener.listen(port) != sf::Socket::Done){
        cerr << "ERROR: listener cannot be started" << endl;
        return -1;
    }
    data.numClient = 0;
    data.cmd = '\0';
    if(pthread_create(&data.threadID, NULL, connectionHandler, (void *)&data) < 0){
        data.listener.close();
        cerr << "ERROR: connectionHandler cannot be created!" << endl;
		return -1;
	}
    pthread_join(data.threadID, nullptr);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void Commander::stop() 
{
    data.sound.stop();
    if(data.isOnline){
        data.socket.disconnect();
        data.listener.close();
        DEBUG_PRINT("Server is disconnected\n");
    }
}