#include "ByteStream.hpp"

using namespace Weber;

size_t ByteStream::getSequence(Byte *buffer, size_t n) {
    size_t count = 0;
    while (count < n && this->readyForGiving()) {
        buffer[count] = this->getByte();
        count++;
    }
    return count;
}

size_t ByteStream::putSequence(Byte *buffer, size_t n) {
    size_t count = 0;
    while (count < n && this->readyForAccepting()) {
        this->putByte(buffer[count]);
        count++;
    }
    return count;
}

ByteStream::~ByteStream() {
}
