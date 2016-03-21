#include <stdio.h>
#include "NetworkManager.h"

#include <iostream>
#include <list>

void showBuff(char *buff, int len) {
    std::cout << "Len " << len << std::endl;
    for (int i = 0; i < len; i++) {
        std::cout << static_cast<unsigned int>(buff[i]) << " ";
    }
    std::cout << std::endl;
}

int main(int argc, const char *argv[]) {
    NetworkManager networkManager;

    if (networkManager.init() == -1) {
        return EXIT_FAILURE;
    }

    networkManager.setOnNewClientConnect([](int fd) { std::cout << "New connexion " << fd << std::endl; });
    networkManager.setOnClientTalk(showBuff);

    while (1) {
        if (networkManager.process() == -1) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
