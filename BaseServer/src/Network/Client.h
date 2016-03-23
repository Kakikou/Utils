//
// Created by Kevin Rodrigues on 15/03/2016.
//

#ifndef CLIENT_H
#define CLIENT_H

namespace Network {
    class Client {
    public:
        Client(int socket);
        ~Client();

        int getSocket() const;
        void setSocket(int socket);

    private:
        int socket;
    };
}

#endif //CLIENT_H
