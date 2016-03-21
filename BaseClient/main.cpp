#include <iostream>
#include "src/Socket.h"
#include "src/Protocol.h"
#include "src/NetworkBuffer.h"

int main() {
    Socket socket("localhost", 4242);

    socket.connectSocket();
    while (1) {
        std::string str;
        std::cin >> str;

        Header header;
        header.type = 12;
        Data data;
        data.data[0] = 127;

        NetworkBuffer networkBuffer;
        networkBuffer << std::make_pair(static_cast<void *>(&header), sizeof(header));
        networkBuffer << std::make_pair(static_cast<void *>(&data), sizeof(data));
        socket.send(networkBuffer);
    }
    return 0;
}