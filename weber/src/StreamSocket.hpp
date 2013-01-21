#ifndef STREAM_SOCKET_HPP
#define STREAM_SOCKET_HPP

#include "Socket.hpp"
#include "ByteStream.hpp"

namespace Weber {

    class StreamSocket: public Socket, public ByteStream {
      public:
        explicit StreamSocket(int fd);
        StreamSocket(const StreamSocket &s);

        StreamSocket& operator =(const StreamSocket &s);

        ~StreamSocket();

        virtual bool readyForGiving();
        virtual Byte getByte();
        virtual size_t getSequence(Byte *buffer, size_t n);

        virtual bool readyForAccepting();
        virtual void putByte(Byte b);
        virtual size_t putSequence(Byte *buffer, size_t n);
    };
}

#endif
