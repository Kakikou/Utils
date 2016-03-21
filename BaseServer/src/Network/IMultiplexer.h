//
// Created by Kevin Rodrigues on 21/03/2016.
//

#ifndef BASESERVER_IMULTIPLEXER_H
#define BASESERVER_IMULTIPLEXER_H

class IMultiplexer {
public:
    virtual ~IMultiplexer() { };

    virtual void process() = 0;

    virtual void setTimeout(int to) = 0;
    virtual void reset() = 0;
    virtual void initRead() = 0;
    virtual void initWrite() = 0;
    virtual void addRead(int read) = 0;
    virtual void addWrite(int write) = 0;
    virtual void removeRead(int toRemove) = 0;
    virtual void removeWrite(int toRemove) = 0;
    virtual bool issetReads(const int) = 0;
    virtual bool issetWrites(const int) = 0;
};

#endif //BASESERVER_IMULTIPLEXER_H
