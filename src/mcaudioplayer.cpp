/*!
    \file mcaudioplayer.cpp
    \brief audio player with TCP server
    \author Mehmet Cihangir
    \date 18.05.2024
    \copyright NA
*/
#include "common.h" 
#include "tcpserver.h" 
#include "commander.h" 
#include <SFML/Audio.hpp>


using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////
static void * commandHandler(void * arg)
{
    bool flag = true;

	pthread_detach(pthread_self());

   	pthread_exit(NULL);
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
    cout << "Arg count: " << argc << std::endl;

    for (int i = 0; i < argc; ++i) {
        std::cout << "Arg " << i << ": " << argv[i] << std::endl;
    }
    int val = 12;
    val++;
    DEBUG_PRINT("test :%d", val);

    //=====================================================
	if(argc < 2) {
        cerr << "ERROR: Usage: ./mcaudioplayer auido_file [TCP port]" << endl;
		return 0;
	}
    int port = 55000;
	if(argc == 3){
		port = atoi(argv[2]);
    }


    sf::SoundBuffer buffer;
    
    if (!buffer.loadFromFile(argv[1])) {
        cerr << "ERROR: Usage: ./mcaudioplayer auido_file [TCP port]" << endl;
        cerr << "ERROR: Please enter the path of the audio file like /home/mypc/test.wav" << endl;
        return -1;
    }
    sf::Sound sound;
    sound.setBuffer(buffer);

    Commander commander;
    commander.start(port);

    pthread_t threadID;
    if(pthread_create(&threadID, NULL, commandHandler, (void *)&sound) < 0){
        cerr << "ERROR: commandHandler cannot be created!" << endl;
		return -1;
	}


    while(1){

        if(commander.data.cmd == 'p'){
            sound.play();
            commander.data.cmd  = ' ';
        }
        if(commander.data.cmd == 's'){
            sound.stop();
            commander.data.cmd  = ' ';
        }
        if(commander.data.cmd == 'q'){
            break;
        }
        sleep(1);
        //DEBUG_PRINT("waiting for data\n");
    }

    commander.stop();
    return 0;
}