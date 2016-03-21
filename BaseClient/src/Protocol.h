//
// Created by Kevin Rodrigues on 21/03/2016.
//

#ifndef PROTOCOL_H
#define PROTOCOL_H

struct Header {
    int type;
};

struct Data {
    char data[20];
};

#endif // PROTOCOL_H
