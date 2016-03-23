//
// Created by Kevin Rodrigues on 17/03/2016.
//

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H


#include <functional>
#include <vector>
#include "IMultiplexer.h"
#include "Client.h"

namespace Network {
    class NetworkManager {
    public:
        NetworkManager();
        ~NetworkManager();

        static const int PORT = 4242;
        static const int MAX_CLIENT = 100;

        int init();
        int process();

        void setOnNewClientConnect(std::function<void(Client *)> const &newClientCallback);
        void setOnClientTalk(std::function<void(Client *, char *, int)> const &clientTalk);


    private:
        int maxFd;
        int mainSocket;
        std::vector<Client *> connectedClient;
        std::function<void(Client *)> newClientCallback;
        std::function<void(Client *, char *, int)> clientTalk;

        IMultiplexer *multiplexer;

        void resetMaxFd();
        int initMainSocket();
        Client *handleNewConnection();
        void removeClient(Client *toRemove);
    };
}


#endif //NETWORKMANAGER_H
