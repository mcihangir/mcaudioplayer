////////////////////////////////////////////////////////////
//
// TCP Server & Audio Player with SFML - Simple and Fast Multimedia Library
// 2024 Mehmet Cihangir (mehmet.cihangir@yahoo.com)
//
////////////////////////////////////////////////////////////
#include "common.h" 
#include "commander.h" 
#define _VERSION "v1.0"

///////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) 
{
    DEBUG_PRINT("mcaudioplayer %s\n", _VERSION);
	if(argc < 2) {
        cerr << "ERROR: Usage: ./mcaudioplayer auido_file [TCP port]" << endl;
		return 0;
	}
    int port = 55000;
	if(argc == 3){
		port = atoi(argv[2]);
    }
    Commander commander;
    commander.start(argv[1], port);
    commander.stop();
    DEBUG_PRINT("Good bye!\n");
    return 0;
}