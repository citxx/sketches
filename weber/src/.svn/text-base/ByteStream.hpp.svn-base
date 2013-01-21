#ifndef BYTE_STREAM_HPP
#define BYTE_STREAM_HPP

#include <sys/types.h>

namespace Weber {

    typedef char Byte;

    class ByteStream {
      public:
        virtual ~ByteStream();

        virtual bool readyForGiving() = 0;
        virtual Byte getByte() = 0;
        virtual size_t getSequence(Byte *buffer, size_t n);

        virtual bool readyForAccepting() = 0;
        virtual void putByte(Byte b) = 0;
        virtual size_t putSequence(Byte *buffer, size_t n);
    };
}

#endif
