//
// Created by Kevin Rodrigues on 21/03/2016.
//
#ifndef NETWORKBUFFER_H_
#define NETWORKBUFFER_H_

#include <iostream>
#include <typeinfo>
#include "IBuffer.h"

class NetworkBuffer : public IBuffer {
public:
    NetworkBuffer(unsigned int size = 2048);

    virtual ~NetworkBuffer();

    static bool isBigEndian() {
        static const short dummy_value = 0x00FF;
        static const char *dummy_tab = reinterpret_cast<const char *>(&dummy_value);

        return (dummy_tab[0] == 0x00);
    }

    virtual IBuffer &operator<<(const int &);
    virtual IBuffer &operator<<(const unsigned int &);
    virtual IBuffer &operator<<(const uint64_t &);
    virtual IBuffer &operator<<(const float &);
    virtual IBuffer &operator<<(const std::string &);
    virtual IBuffer &operator<<(const char &);
    virtual IBuffer &operator<<(std::pair<void *, size_t> pair);
    virtual IBuffer &operator>>(int &);
    virtual IBuffer &operator>>(unsigned int &);
    virtual IBuffer &operator>>(uint64_t &);
    virtual IBuffer &operator>>(float &);
    virtual IBuffer &operator>>(std::string &);
    virtual IBuffer &operator>>(char &);

    virtual const char *getBuffer() const;
    virtual char *getBuffer();
    virtual unsigned int getLength() const;
    virtual unsigned int getPosition() const;
    virtual void setPosition(unsigned int position);

protected:
    char *buffer;
    unsigned int current_pos;
    unsigned int buffer_size;

private:
    template<typename T>
    void serialize(const T &elements) {
        int i;
        const char *tab;

        tab = reinterpret_cast<const char *>(&elements);
        if (this->current_pos + sizeof(T) > this->buffer_size) {
            return;
        }
        if (isBigEndian())
            i = 0;
        else
            i = sizeof(T) - 1;
        while ((isBigEndian() && i < static_cast<int>(sizeof(T))) || (!isBigEndian() && i >= 0)) {
            this->buffer[this->current_pos] = tab[i];
            if (isBigEndian())
                ++i;
            else
                --i;
            this->setPosition(this->getPosition() + 1);
        }
    };

    template<typename T>
    void unserialize(T &elements) {
        int i;
        char *tab;

        tab = reinterpret_cast<char *>(&elements);
        if (this->buffer_size - this->current_pos < sizeof(T)) {
            return;
        }
        if (isBigEndian()) {
            i = 0;
        } else {
            i = sizeof(T) - 1;
        }
        while ((isBigEndian() && i < static_cast<int>(sizeof(T))) || (!isBigEndian() && i >= 0)) {
            tab[i] = this->buffer[this->current_pos];
            if (isBigEndian())
                ++i;
            else
                --i;
            ++this->current_pos;
        }
    }
};

template<>
void NetworkBuffer::serialize<std::string>(const std::string &element);

template<>
void NetworkBuffer::serialize<std::pair<void *, size_t>>(const std::pair<void *, size_t> &pair);

template<>
void NetworkBuffer::unserialize<std::string>(std::string &element);

#endif // NETWORKBUFFER_H_
