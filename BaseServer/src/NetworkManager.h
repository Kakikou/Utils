//
// Created by Kevin Rodrigues on 17/03/2016.
//

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H


#include <functional>
#include <vector>
#include "Network/IMultiplexer.h"

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();

    static const int PORT = 4242;
    static const int MAX_CLIENT = 100;

    int init();
    int process();

    void setOnNewClientConnect(std::function<void(int)> const &newClientCallback);
    void setOnClientTalk(std::function<void(char *, int)> const &clientTalk);


private:
    int maxFd;
    int mainSocket;
    fd_set readFdSet;
    std::vector<int> openedSocket;
    std::function<void(int)> newClientCallback;
    std::function<void(char *, int)> clientTalk;

    IMultiplexer *multiplexer;

    void resetMaxFd();
    int initMainSocket();
    int handleNewConnection();
    void removeSocket(int socketToRemove);
};


#endif //NETWORKMANAGER_H
