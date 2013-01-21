#ifndef WEBER_WEBSERVER_H
#define WEBER_WEBSERVER_H

#include <sys/types.h>

#include "Listener.hpp"

namespace Weber {

    class WebServer {
        pid_t pid;
        Listener *socket;
        bool isRunning;

        static void termHandler(int sig);

      public:
        WebServer();
        ~WebServer();

        void start(int port = 2323);
        void stop();
    };
}

#endif
