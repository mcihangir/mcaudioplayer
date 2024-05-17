cmake_minimum_required(VERSION 3.10)

project(mcaudioplayer)

set(CMAKE_CXX_STANDARD 11)

#set(SRC_DIR src)
#set(INC_DIR include)
#set(BUILD_DIR build)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
#set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_NAME mcaudioplayer)

set(SOURCES
    ${SRC_DIR}/mcaudioplayer.cpp
    ${SRC_DIR}/commander.cpp
)

#file(MAKE_DIRECTORY ${BUILD_DIR})
# Set CMAKE_BUILD_TYPE to "Release"
#set(CMAKE_BUILD_TYPE Release)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_link_libraries(${EXECUTABLE_NAME} pthread sfml-network sfml-audio sfml-window)
target_include_directories(${EXECUTABLE_NAME}
    PRIVATE ${INC_DIR}
)