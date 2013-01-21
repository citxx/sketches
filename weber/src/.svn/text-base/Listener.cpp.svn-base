#include "Listener.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

using namespace Weber;

Listener::Listener(int port): Socket() {
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(this->fd(), (struct sockaddr*)&address, sizeof(address)) < 0) {
        const char *context = "System call 'bind'";
        switch (errno) { // TODO: Exceptions
            case EACCES:
            case EADDRINUSE:
            case EBADF:
            case EINVAL:
            case ENOTSOCK:
                throw context;
        }
    }

    if (listen(this->fd(), Listener::backLog) < 0) {
        const char *context = "System call 'listen'";
        switch (errno) { // TODO: Exceptions
            case EADDRINUSE:
            case EBADF:
            case ENOTSOCK:
            case EOPNOTSUPP:
                throw context;
        }
    }
}

Listener::Listener(const Listener &l): Socket(l) {
}

Listener::~Listener() {
}

Listener& Listener::operator =(const Listener &l) {
    this->Socket::operator =(l);
    return *this;
}

StreamSocket Listener::accept() const {
    struct sockaddr_in clientAddress;
    int clientSocket;
    socklen_t clientAddressLen;

    clientSocket = ::accept(
        this->fd(),
        (struct sockaddr*)&clientAddress,
        &clientAddressLen);

    if (clientSocket < 0) {
        const char *context = "System call 'accept'";
        switch (errno) { // TODO: Exceptions
            case EAGAIN:
            case EBADF:
            case ECONNABORTED:
            case EFAULT:
            case EINVAL:
            case ENOTSOCK:
            case EOPNOTSUPP:
            case EINTR:
            case EMFILE:
            case ENFILE:
            case ENOBUFS: case ENOMEM:
            case EPROTO:
            case EPERM:
            case ENOSR: case ESOCKTNOSUPPORT: case EPROTONOSUPPORT: case ETIMEDOUT:
                throw context;
        }
    }

    return StreamSocket(clientSocket);
}

