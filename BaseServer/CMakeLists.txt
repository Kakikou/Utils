cmake_minimum_required(VERSION 3.3)
project(BaseServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/main.cpp
        src/NetworkManager.cpp
        Client.cpp)

set(INCLUDES
        src/NetworkManager.h
        Client.h)

add_executable(BaseServer ${SOURCE_FILES} ${INCLUDES})