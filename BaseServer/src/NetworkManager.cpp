//
// Created by Kevin Rodrigues on 17/03/2016.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <iostream>
#include "NetworkManager.h"

NetworkManager::NetworkManager() {

}

NetworkManager::~NetworkManager() {

}

int NetworkManager::init() {
    int err;
    err = initMainSocket();
    resetMaxFd();
    return err;
}

void NetworkManager::setOnNewClientConnect(std::function<void(int)> const &newClientCallback) {
    this->newClientCallback = newClientCallback;
}

void NetworkManager::setOnClientTalk(std::function<void(char *, int)> const &clientTalk) {
    this->clientTalk = clientTalk;
}

int NetworkManager::process() {
    FD_ZERO(&readFdSet);
    FD_SET(STDIN_FILENO, &readFdSet);
    FD_SET(mainSocket, &readFdSet);

    for (int socket : openedSocket) {
        FD_SET(socket, &readFdSet);
    }

    if (select(maxFd + 1, &readFdSet, nullptr, nullptr, nullptr) == -1) {
        perror("select()");
        return -1;
    }

    if (FD_ISSET(STDIN_FILENO, &readFdSet)) {
        char buff[512];
        bzero(buff, 512);
        read(STDIN_FILENO, buff, 512);
    }

    if (FD_ISSET(mainSocket, &readFdSet)) {
        int newConnexion = handleNewConnection();
        newClientCallback(newConnexion);
    }

    for (int socket : openedSocket) {
        if (FD_ISSET(socket, &readFdSet)) {
            char *buff = new char[512];
            bzero(buff, 512);
            ssize_t len = read(socket, buff, 512);
            if (len == 0) {
                std::cout << "Socket " << socket << " disconnect" << std::endl;
                removeSocket(socket);
            } else {
                clientTalk(buff, len);
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

int NetworkManager::handleNewConnection() {
    struct sockaddr_in csin = {0};
    socklen_t sinsize = sizeof csin;

    int csock = accept(mainSocket, (struct sockaddr *) &csin, &sinsize);

    if (csock == -1) {
        perror("accept()");
        return -1;
    }
    openedSocket.push_back(csock);
    resetMaxFd();
    return csock;
}

void NetworkManager::removeSocket(int socketToRemove) {
    close(socketToRemove);
    openedSocket.erase(std::remove(openedSocket.begin(), openedSocket.end(), socketToRemove), openedSocket.end());
    resetMaxFd();
}

void NetworkManager::resetMaxFd() {
    maxFd = mainSocket;
    for (int socket : openedSocket) {
        maxFd = (socket > maxFd) ? socket : maxFd;
    }
}
