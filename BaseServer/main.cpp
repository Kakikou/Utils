#include "src/Server.h"

#include <iostream>

int main(int argc, const char *argv[]) {
    Server server;

    if (server.prepare(argc, argv) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    return server.run();
}
