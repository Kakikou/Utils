//
// Created by Kevin Rodrigues on 21/03/2016.
//

#ifndef BASESERVER_SELECT_H
#define BASESERVER_SELECT_H

#include <sys/types.h>
#include "IMultiplexer.h"

namespace Network {
    class Select : public IMultiplexer {
    public:
        Select();
        virtual ~Select();

        virtual void process() override;
        virtual void setTimeout(int to) override;
        virtual void reset() override;
        virtual void addRead(int read) override;
        virtual void addWrite(int write) override;
        virtual void removeRead(int toRemove) override;
        virtual void removeWrite(int toRemove) override;
        virtual bool issetReads(const int i) override;
        virtual bool issetWrites(const int i) override;
        virtual void initRead() override;
        virtual void initWrite() override;

    private:
        int max_fd;

        fd_set *fd_set_read;
        fd_set *fd_set_write;
        struct timeval *tv;
    };
}

#endif //BASESERVER_SELECT_H
