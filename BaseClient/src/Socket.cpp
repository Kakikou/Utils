//
// Created by Kevin Rodrigues on 21/03/2016.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "Socket.h"

#if defined(__APPLE__) || defined(__MACH__)
# ifndef MSG_NOSIGNAL
#  define MSG_NOSIGNAL SO_NOSIGPIPE
# endif
#endif

Socket::Socket(const std::string &hostname, int port) : hostname(hostname), port(port) {
}

Socket::~Socket() {
}

bool Socket::connectSocket() {
    struct sockaddr_in sin = {0};
    struct hostent *hostinfo = nullptr;

    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket()");
        return false;
    }

    hostinfo = gethostbyname(this->hostname.c_str());
    if (hostinfo == nullptr) {
        fprintf(stderr, "Unknown host %s.\n", this->hostname.c_str());
        return false;
    }

    sin.sin_addr = *(struct in_addr *) hostinfo->h_addr;
    sin.sin_port = htons(this->port);
    sin.sin_family = AF_INET;

    if (connect(sock, (struct sockaddr *) &sin, sizeof(struct sockaddr)) == -1) {
        perror("Connect()");
        return false;
    }
    return true;
}


bool Socket::send(IBuffer &buff) {
    return ::send(this->sock, buff.getBuffer(), buff.getPosition(), MSG_NOSIGNAL) > 0;
}

bool Socket::send(void *data, size_t size) {
    return ::send(this->sock, data, size, MSG_NOSIGNAL) > 0;
}
