#include <iostream>
#include <net/server.h>
#include <thread>

void runServer() {}

void runClient(std::string name) {}

int main(int argc, char **argv)
{
    if (argc < 3) {
        std::cout << "Please enter `server/client name`" << std::endl;
        return 0;
    }

    std::string kind = argv[1];
    std::string name = argv[2];

    if (kind == "server") {
        runServer();
        runClient(name);
    }
    else if (kind == "client") {
        runClient(name);
    }
}