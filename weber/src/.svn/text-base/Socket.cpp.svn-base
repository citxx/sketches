#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#include "Socket.hpp"

#include <iostream> // TO REMOVE

using namespace Weber;

Socket::Socket() {
    this->common = new CommonFD; // TODO: check if it safe
    this->common->count = 1;
    this->common->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->common->fd < 0) {
        delete this->common;
        const char *context = "System call 'socket'";
        switch (errno) { // TODO: Exceptions
            case EACCES:
            case EAFNOSUPPORT:
            case EINVAL:
            case EMFILE:
            case ENFILE:
            case ENOBUFS: case ENOMEM:
            case EPROTONOSUPPORT:
                throw context;
        }
    }

}

Socket::Socket(int fd) {
    if (fd < 0) { // TODO: Exceptions
        throw "Invalid descriptor";
    }
    this->common = new CommonFD; // TODO: check if safe
    this->common->count = 1;
    this->common->fd = fd;
}

Socket::Socket(const Socket &s) {
    this->common = s.common;
    this->common->count += 1;
}

void Socket::clean() throw() {
    this->common->count -= 1;
    if (this->common->count == 0) {
        shutdown(this->common->fd, SHUT_RDWR);
        close(this->common->fd);
        delete this->common;
    }
}

Socket& Socket::operator =(const Socket &s) {
    this->clean();
    this->common = s.common;
    this->common->count += 1;
    return *this;
}

int Socket::fd() const throw() {
    return this->common->fd;
}

Socket::~Socket() throw() {
    this->clean();
}
