#include <iostream>
#include <string>
#include <cstdlib>

#include "WebServer.hpp"

int main(int argc, char *argv[]) {
    try {
        Weber::WebServer server;

        server.start(2323); // We ask the server to do all the work...

        for (;;) { // ... while we recieve commands from user
            std::string command;
            std::getline(std::cin, command);
            command.erase(command.find_last_not_of(' ') + 1);
            command.erase(0, command.find_first_not_of(' '));
            if (command == "quit") { // Server may have some rest now
                server.stop();
                break;
            }
        }
    }
    catch (const char *answer) { // He don't want to help us =(
        std::cerr << answer << std::endl;
        exit(EXIT_FAILURE);
    }
/*    catch (const Weber::Exception &e) {
        std::cerr << e.getMessage() << std::endl;
    }*/

    return 0;
}
