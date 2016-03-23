//
// Created by Kevin Rodrigues on 15/03/2016.
//

#include "Client.h"

namespace Network {
    Client::Client(int socket) : socket(socket) {

    }

    Client::~Client() {

    }

    int Client::getSocket() const {
        return this->socket;
    }

    void Client::setSocket(int socket) {
        this->socket = socket;
    }
}
