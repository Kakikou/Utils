//
// Created by Kevin Rodrigues on 21/03/2016.
//

#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "IBuffer.h"

class Socket {
public:
    Socket(const std::string &hostname, int port);
    ~Socket();

    bool connectSocket();
    bool send(IBuffer &buff);
    bool send(void *data, size_t size);
    void close();

private:
    const int port;
    const std::string hostname;

    int sock;
};


#endif // CLIENT_H
