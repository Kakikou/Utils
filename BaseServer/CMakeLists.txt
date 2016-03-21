cmake_minimum_required(VERSION 3.3)
project(BaseServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        src/NetworkManager.cpp
        src/Client.cpp)

set(INCLUDES
        src/NetworkManager.h
        src/Client.h)

add_executable(BaseServer ${SOURCE_FILES} ${INCLUDES})