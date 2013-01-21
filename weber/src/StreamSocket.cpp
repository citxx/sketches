#include "StreamSocket.hpp"

using namespace Weber;

StreamSocket::StreamSocket(int fd): Socket(fd) {
}

StreamSocket::StreamSocket(const StreamSocket &s): Socket(s) {
}

StreamSocket::~StreamSocket() {
}

StreamSocket& StreamSocket::operator =(const StreamSocket &s) {
    this->Socket::operator =(s);
    return *this;
}

