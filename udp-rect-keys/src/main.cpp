#include <iostream>
#include <thread>
#include <SFML/Network/IpAddress.hpp>

#include "client/application.h"
#include "server/server.h"

int main(int argc, char **argv)
{
    std::cout << sf::IpAddress::getLocalAddress() << std::endl;
    if (argc < 3) {
        std::cout << "Please enter `server/client name`" << std::endl;
        return 0;
    }

    std::string kind = argv[1];
    std::string name = argv[2];

    if (kind == "server") {
        Server server;
        server.run();
    }
    else if (kind == "client") {
        Application app;
        app.run();
    }
}