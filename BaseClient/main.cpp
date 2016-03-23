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

        if (str == "1")
            break;

        Header header = { 0 };
        header.type = 12;
        Data data = { 0 };
        data.data[0] = 127;

        NetworkBuffer networkBuffer;
        networkBuffer << std::make_pair(static_cast<void *>(&header), sizeof(header));
        networkBuffer << std::make_pair(static_cast<void *>(&data), sizeof(data));
        socket.send(networkBuffer);
    }
    socket.close();
    return 0;
}