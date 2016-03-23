//
// Created by Kevin Rodrigues on 23/03/2016.
//

#ifndef BASESERVER_SERVER_H
#define BASESERVER_SERVER_H

#include "Network/Client.h"
#include "Network/NetworkManager.h"

class Server {
public:
    Server();
    virtual ~Server();

    int prepare(int argc, char const **argv);
    int run();

private:
    void showBuff(Network::Client *client, char *buff, int len);

    Network::NetworkManager networkManager;
};


#endif //BASESERVER_SERVER_H
