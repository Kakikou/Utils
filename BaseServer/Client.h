//
// Created by Kevin Rodrigues on 15/03/2016.
//

#ifndef MOCKMARKETTEST_CLIENT_H
#define MOCKMARKETTEST_CLIENT_H


class Client {
public:
    Client(int socket);
    ~Client();

    int getSocket() const;
    void setSocket(int socket);

private:
    int socket;
};


#endif //MOCKMARKETTEST_CLIENT_H
