#include "WebServer.hpp"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <signal.h>
#include <errno.h>

#include <iostream>

using namespace Weber;

WebServer::WebServer():
    socket(NULL),
    isRunning(false) {
}

WebServer *server = NULL;
void WebServer::termHandler(int sig) {
    std::cerr << "SIGTERM caught" << std::endl; // TO REMOVE

    delete server->socket;
    delete server;

    exit(EXIT_SUCCESS);
}

void WebServer::start(int port) {
    if (this->isRunning) { // TODO: Exceptions
        throw "Server is already running";
    }

    this->socket = new Listener(port); // TODO: Exceptions

    this->pid = fork(); // TODO: Exceptions
    if (this->pid < 0) {
        throw "Unable to start Weber: error occured while fork call was performed";
    }

    this->isRunning = true; // Success. Our server is almost started

    if (this->pid > 0) { // Parent. We return the control to main programm
        delete this->socket;
        return;
    }

    // Child. We start our web server completely. Control no longer return to the main programm
    try {
        server = this;
        signal(SIGTERM, termHandler);

//        for (;;) { // Every iteration we accept one request
//        }

    }
    catch (const char *err) {
        std::cerr << "WebServer: " << err << std::endl;
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

void WebServer::stop() {
    if (this->isRunning) {
        if (this->pid > 0) {
            int status = kill(this->pid, SIGTERM); // No, not kill. Only allow to stop work
            if (status == -1) { // What? This swine is gone. Arrrgh!
                throw "Error occured while kill call was performed";
            }
            waitpid(this->pid, &status, 0);
            this->pid = -1;
        }
        else { // How do you call this method from the child? It's impossible
            throw "Apocalypse is comming";
        }
    }
    else { // What? Are you sure? It has already stopped. You are crazy!
        throw "Error: Attempt to stop not started server";
    }
}

WebServer::~WebServer() {
}
