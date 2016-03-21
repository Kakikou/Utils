cmake_minimum_required(VERSION 3.3)
project(BaseClient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        src/Socket.cpp
        src/NetworkBuffer.cpp)

set(INCLUDES
        src/Socket.h
        src/IBuffer.h
        src/NetworkBuffer.h
        src/Protocol.h)

add_executable(BaseClient ${SOURCE_FILES} ${INCLUDES})