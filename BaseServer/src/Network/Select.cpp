//
// Created by Kevin Rodrigues on 21/03/2016.
//

#include <sys/socket.h>
#include <sys/select.h>
#include <cstdio>
#include "Select.h"


namespace Network {
    Select::Select() : max_fd(0), fd_set_read(nullptr), fd_set_write(nullptr), tv(nullptr) {

    }

    Select::~Select() {

    }

    void Select::process() {
        if (::select(max_fd + 1, fd_set_read, fd_set_write, nullptr, tv) == -1) {
            perror("Select()");
        }
    }

    void Select::setTimeout(int to) {
        if (tv == nullptr) {
            tv = new struct timeval;
        }
        tv->tv_sec = to;
    }

    void Select::reset() {
        this->max_fd = 0;
        FD_ZERO(fd_set_read);
        FD_ZERO(fd_set_write);
    }

    void Select::addRead(int read) {
        if (read > max_fd) {
            max_fd = read;
        }
        FD_SET(read, fd_set_read);
    }

    void Select::addWrite(int write) {
        if (write > max_fd) {
            max_fd = write;
        }
        FD_SET(write, fd_set_write);
    }

    void Select::removeRead(int toRemove) {
        FD_CLR(toRemove, fd_set_read);
    }

    void Select::removeWrite(int toRemove) {
        FD_CLR(toRemove, fd_set_write);
    }

    bool Select::issetReads(const int fd) {
        return FD_ISSET(fd, fd_set_read) != 0;
    }

    bool Select::issetWrites(const int fd) {
        return FD_ISSET(fd, fd_set_write) != 0;
    }

    void Select::initRead() {
        fd_set_read = new fd_set();
        FD_ZERO(fd_set_read);
    }

    void Select::initWrite() {
        fd_set_write = new fd_set();
        FD_ZERO(fd_set_write);
    }

}
