cmake_minimum_required(VERSION 3.10)

project(mcaudioplayer)

set(CMAKE_CXX_STANDARD 11)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
#set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)

# If the SFML is not installed in the standard path
#set(SFML_ROOT "/custom/path/to/sfml")
# Add Include and library directories
#include_directories("${SFML_ROOT}/include")
#link_directories("${SFML_ROOT}/lib")

set(EXECUTABLE_NAME mcaudioplayer)

set(SOURCES
    ${SRC_DIR}/mcaudioplayer.cpp
    ${SRC_DIR}/commander.cpp
)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_link_libraries(${EXECUTABLE_NAME} pthread sfml-network sfml-audio)
target_include_directories(${EXECUTABLE_NAME}
    PRIVATE ${INC_DIR}
)