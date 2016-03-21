//
// Created by Kevin Rodrigues on 21/03/2016.
//

#ifndef MOCKMARKETCLIENT_PROTOCOL_H
#define MOCKMARKETCLIENT_PROTOCOL_H

struct Header {
    int type;
};

struct Data {
    char data[20];
};

#endif //MOCKMARKETCLIENT_PROTOCOL_H
