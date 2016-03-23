//
// Created by Kevin Rodrigues on 17/03/2016.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "NetworkManager.h"
#include "Select.h"

namespace Network {
    NetworkManager::NetworkManager() {
        multiplexer = new Network::Select();
        multiplexer->initRead();
        multiplexer->initWrite();
    }

    NetworkManager::~NetworkManager() {

    }

    int NetworkManager::init() {
        int err;
        err = initMainSocket();
        resetMaxFd();
        return err;
    }

    void NetworkManager::setOnNewClientConnect(std::function<void(Client *)> const &newClientCallback) {
        this->newClientCallback = newClientCallback;
    }

    void NetworkManager::setOnClientTalk(std::function<void(Client *, char *, int)> const &clientTalk) {
        this->clientTalk = clientTalk;
    }

    int NetworkManager::process() {
        multiplexer->reset();
        multiplexer->addRead(STDIN_FILENO);
        multiplexer->addRead(mainSocket);

        for (Client *client : connectedClient) {
            multiplexer->addRead(client->getSocket());
        }

        multiplexer->process();

        if (multiplexer->issetReads(STDIN_FILENO)) {
            char buff[512];
            bzero(buff, 512);
            read(STDIN_FILENO, buff, 512);
        }

        if (multiplexer->issetReads(mainSocket)) {
            Client *newClient = handleNewConnection();
            newClientCallback(newClient);
        }

        for (Client *client : connectedClient) {
            if (multiplexer->issetReads(client->getSocket())) {
                char *buff = new char[512];
                bzero(buff, 512);
                ssize_t len = read(client->getSocket(), buff, 512);
                if (len == 0) {
                    std::cout << "Socket " << client->getSocket() << " disconnect" << std::endl;
                    removeClient(client);
                } else {
                    clientTalk(client, buff, len);
                }
                delete buff;
            }
        }
        return 0;
    }

    int NetworkManager::initMainSocket() {
        mainSocket = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in sin = {0};

        if (mainSocket == -1) {
            perror("socket()");
            return -1;
        }

        sin.sin_addr.s_addr = htonl(INADDR_ANY);
        sin.sin_port = htons(PORT);
        sin.sin_family = AF_INET;

        if (bind(mainSocket, (struct sockaddr *) &sin, sizeof sin) == -1) {
            perror("bind()");
            return -1;
        }

        if (listen(mainSocket, MAX_CLIENT) == -1) {
            perror("listen()");
            return -1;
        }
        return 0;
    }

    Client *NetworkManager::handleNewConnection() {
        struct sockaddr_in csin = {0};
        socklen_t sinsize = sizeof csin;

        int csock = accept(mainSocket, (struct sockaddr *) &csin, &sinsize);

        if (csock == -1) {
            perror("accept()");
            return nullptr;
        }
        Client *client = new Client(csock);
        connectedClient.push_back(client);
        resetMaxFd();
        return client;
    }

    void NetworkManager::removeClient(Client *toRemove) {
        close(toRemove->getSocket());
        connectedClient.erase(std::remove(connectedClient.begin(), connectedClient.end(), toRemove), connectedClient.end());
        resetMaxFd();
    }

    void NetworkManager::resetMaxFd() {
        maxFd = mainSocket;
        for (Client *client : connectedClient) {
            maxFd = (client->getSocket() > maxFd) ? client->getSocket() : maxFd;
        }
    }
}
