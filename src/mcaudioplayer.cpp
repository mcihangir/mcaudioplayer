/*!
    \file mcaudioplayer.cpp
    \brief audio player with TCP server
    \author Mehmet Cihangir
    \date 18.05.2024
    \copyright NA
*/
//#include <conio.h>
#include "common.h" 
#include "commander.h" 

#include <termios.h>
#include <unistd.h>
#include <iostream>

#include <SFML/Window/Keyboard.hpp>
//#include <SFML/Window/Event.hpp>

using namespace std;


///////////////////////////////////////////////////////////////////////////////////////////////////////
static void * keyReader(void * arg)
{
    struct Commander *commander = (Commander *)arg;

    DEBUG_PRINT("Press e to exit.\n");
    DEBUG_PRINT("Press UP and DOWN arrows to set the volume.\n");

    while(1){        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            std::cout << "\033[2J\033[H"; // Clear the terminal line
            commander->data.sound.setVolume((commander->data.sound.getVolume() + 10)>100?100:(commander->data.sound.getVolume() + 10));            
            DEBUG_PRINT("Volume: %f\n", commander->data.sound.getVolume());
            usleep(100000);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            std::cout << "\033[2J\033[H"; // Clear the terminal line
            commander->data.sound.setVolume((commander->data.sound.getVolume() - 10)<0?0:(commander->data.sound.getVolume() - 10));            
            DEBUG_PRINT("Volume: %f\n", commander->data.sound.getVolume());
            usleep(100000);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            commander->stop();
            break;
        }
        usleep(1000);
    }

    pthread_exit(NULL);
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) 
{

	if(argc < 2) {
        cerr << "ERROR: Usage: ./mcaudioplayer auido_file [TCP port]" << endl;
		return 0;
	}
    int port = 55000;
	if(argc == 3){
		port = atoi(argv[2]);
    }

    Commander commander;
    pthread_t threadID;
    pthread_create(&threadID, NULL, keyReader, (void *)&commander);
    commander.start(argv[1], port);
    DEBUG_PRINT("Good bye!\n");
    return 0;
}