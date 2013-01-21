#ifndef WEBER_LISTENER_HPP
#define WEBER_LISTENER_HPP

#include "Socket.hpp"
#include "StreamSocket.hpp"

namespace Weber {

    class Listener: public Socket {
        const static int backLog = 5;

      public:
        explicit Listener(int port);
        Listener(const Listener &l);

        Listener& operator =(const Listener &l);

        ~Listener();

        StreamSocket accept() const;
    };
}

#endif
