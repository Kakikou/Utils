//
// Created by Kevin Rodrigues on 21/03/2016.
//

#ifndef MOCKMARKETCLIENT_CLIENT_H
#define MOCKMARKETCLIENT_CLIENT_H

#include <string>
#include "IBuffer.h"

class Socket {
public:
    Socket(const std::string &hostname, int port);
    ~Socket();

    bool connectSocket();
    bool send(IBuffer &buff);
    bool send(void *data, size_t size);

private:
    const int port;
    const std::string hostname;

    int sock;
};


#endif //MOCKMARKETCLIENT_CLIENT_H
