//
// Created by Kevin Rodrigues on 23/03/2016.
//

#include <iostream>
#include "Server.h"

Server::Server() {

}

Server::~Server() {

}

int Server::prepare(int argc, char const **argv) {
    if (networkManager.init() == -1)
        return EXIT_FAILURE;

    networkManager.setOnNewClientConnect([](Network::Client *client) { std::cout << "New connexion " << client->getSocket() << std::endl; });
    networkManager.setOnClientTalk(std::bind(&Server::showBuff, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    return EXIT_SUCCESS;
}

int Server::run() {
    while (1) {
        if (networkManager.process() == -1) {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

void Server::showBuff(Network::Client *client, char *buff, int len) {
    std::cout << "Len " << len << std::endl;
    for (int i = 0; i < len; i++) {
        std::cout << static_cast<unsigned int>(buff[i]) << " ";
    }
    std::cout << std::endl;
}