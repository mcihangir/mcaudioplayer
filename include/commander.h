////////////////////////////////////////////////////////////
//
// TCP Server with SFML - Simple and Fast Multimedia Library
// 2024 Mehmet Cihangir (mehmet.cihangir@yahoo.com)
//
////////////////////////////////////////////////////////////
#ifndef COMMANDER_H
#define COMMANDER_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <thread>
//#include <vector> 


#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>


using namespace std;

struct commander_data{
	sf::TcpListener listener;
    sf::TcpSocket socket;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	int numClient;
	char cmd;	
    pthread_t threadID;
};

class Commander {
	public:
		int start(char* file, int port);
		void stop();
		commander_data data;
	private:
		static void * connectionHandler(void * arg);
};

#endif