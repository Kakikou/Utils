//
// Created by Kevin Rodrigues on 21/03/2016.
//

#ifndef IBUFFER_H_
#define IBUFFER_H_

#include <string>
#include <cstdint>

class IBuffer {
public:
    virtual ~IBuffer() { }

    virtual const char *getBuffer() const = 0;
    virtual char *getBuffer() = 0;
    virtual unsigned int getLength() const = 0;
    virtual unsigned int getPosition() const = 0;
    virtual void setPosition(unsigned int) = 0;

    virtual IBuffer &operator<<(const int &) = 0;
    virtual IBuffer &operator<<(const unsigned int &) = 0;
    virtual IBuffer &operator<<(const uint64_t &) = 0;
    virtual IBuffer &operator<<(const float &) = 0;
    virtual IBuffer &operator<<(const std::string &) = 0;
    virtual IBuffer &operator<<(const char &) = 0;
    virtual IBuffer &operator<<(std::pair<void *, size_t>) = 0;

    virtual IBuffer &operator>>(int &) = 0;
    virtual IBuffer &operator>>(unsigned int &) = 0;
    virtual IBuffer &operator>>(uint64_t &) = 0;
    virtual IBuffer &operator>>(float &) = 0;
    virtual IBuffer &operator>>(std::string &) = 0;
    virtual IBuffer &operator>>(char &) = 0;
};

#endif // IBUFFER_H_
