#include "NetworkBuffer.h"

NetworkBuffer::NetworkBuffer(unsigned int size) : current_pos(0), buffer_size(size) {
    this->buffer = new char[this->buffer_size];
}

NetworkBuffer::~NetworkBuffer() {
}

const char *NetworkBuffer::getBuffer() const {
    return (this->buffer);
}

char *NetworkBuffer::getBuffer() {
    return (this->buffer);
}

unsigned int        NetworkBuffer::getLength() const {
    return (this->buffer_size);
}

IBuffer &NetworkBuffer::operator<<(const int &value) {
    this->serialize<int32_t>(value);
    return (*this);
}

IBuffer &NetworkBuffer::operator<<(const unsigned int &value) {
    this->serialize<uint32_t>(value);
    return (*this);
}

IBuffer &NetworkBuffer::operator<<(const uint64_t &value) {
    this->serialize<uint64_t>(value);
    return (*this);
}

IBuffer &NetworkBuffer::operator<<(const float &value) {
    this->serialize(value);
    return (*this);
}

IBuffer &NetworkBuffer::operator<<(const std::string &value) {
    this->serialize(value);
    return (*this);
}

IBuffer &NetworkBuffer::operator<<(const char &value) {
    this->serialize(value);
    return (*this);
}

IBuffer &NetworkBuffer::operator<<(std::pair<void *, size_t> pair) {
    this->serialize(pair);
    return (*this);
}

IBuffer &NetworkBuffer::operator>>(int &value) {
    this->unserialize<int32_t>(value);
    return (*this);
}

IBuffer &NetworkBuffer::operator>>(unsigned int &value) {
    this->unserialize<uint32_t>(value);
    return (*this);
}

IBuffer &NetworkBuffer::operator>>(uint64_t &value) {
    this->unserialize<uint64_t>(value);
    return (*this);
}

IBuffer &NetworkBuffer::operator>>(float &value) {
    this->unserialize(value);
    return (*this);
}

IBuffer &NetworkBuffer::operator>>(std::string &value) {
    this->unserialize(value);
    return (*this);
}

IBuffer &NetworkBuffer::operator>>(char &value) {
    this->unserialize(value);
    return (*this);
}

template<>
void NetworkBuffer::serialize<std::string>(const std::string &element) {
    this->serialize(element.length());
    if (this->current_pos + element.length() > this->buffer_size) {
        return;
    }
    for (auto it = element.begin(); it != element.end(); ++it) {
        this->buffer[this->current_pos] = *it;
        this->current_pos++;
    }
}

template<>
void NetworkBuffer::serialize<std::pair<void *, size_t>>(const std::pair<void *, size_t> &pair) {
    char *data = reinterpret_cast<char *>(pair.first);
    for (int i = 0; i < pair.second; i++) {
        this->buffer[this->current_pos] = data[i];
        this->current_pos++;
    }
}

template<>
void NetworkBuffer::unserialize<std::string>(std::string &element) {
    unsigned int size;

    element = "";
    this->unserialize(size);
    if (this->current_pos - this->current_pos < size) {
        return;
    }
    for (unsigned int i = 0; i < size; ++i) {
        element += this->buffer[this->current_pos];
        ++this->current_pos;
    }
}

unsigned int NetworkBuffer::getPosition() const {
    return this->current_pos;
}

void NetworkBuffer::setPosition(unsigned int position) {
    this->current_pos = position;
}
