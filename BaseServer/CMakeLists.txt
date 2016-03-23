cmake_minimum_required(VERSION 3.3)
project(BaseServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        src/Network/NetworkManager.cpp
        src/Network/Client.cpp
        src/Server.cpp
        src/Network/Select.cpp)

set(INCLUDES
        src/Network/NetworkManager.h
        src/Network/Client.h
        src/Network/IMultiplexer.h
        src/Network/Select.h
        src/Server.h)

add_executable(BaseServer ${SOURCE_FILES} ${INCLUDES})