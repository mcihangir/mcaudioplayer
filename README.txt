1. Pre Requirements before compiling mcaudioplayer
Installing SFML
    sudo apt-get install libsfml-dev

In case you installed SFML to a non-standard path, you'll need to tell the compiler where to find the SFML headers (.hpp files):
If you installed SFML to a non-standard path, you'll need to tell the linker where to find the SFML libraries (.so files):
Please edit CMakeLists.txt to add your sfml path as like below

    # If the SFML is not installed in the standard path
    set(SFML_ROOT "/custom/path/to/sfml")
    # Add Include and library directories
    include_directories("${SFML_ROOT}/include")
    link_directories("${SFML_ROOT}/lib")

    run "cmake ."

If you don't have cmake in your Linux Environment you can install it with the following commands:
    sudo apt-get update
    sudo apt-get install cmake


Build the mcaudioplayer
go to mcaudioplayer folder:
    make

In case if you change the CMakeLists.txt:
    cmake .
    make

------------------------------------------------------------------------------------------------------------------------

2. Usage of mcaudioplayer
Usage: ./mcaudioplayer auido_file [TCP port]
[TCP port] is optional. If it is omitted, the listening port will be 55000

Sample1: 
./mcaudioplayer /home/mypc/mcaudioplayer/sound.wav 33000

Sample2: 
./mcaudioplayer ./sound.wav 33000

Sample3: 
./mcaudioplayer ./sound.wav
