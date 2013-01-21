#ifndef WEBER_SOCKET_HPP
#define WEBER_SOCKET_HPP

namespace Weber {

    class Socket {
        struct CommonFD {
            int fd;
            int count;
        } *common;

        void clean() throw();

      protected:
        int fd() const throw();

      public:
        Socket();
        explicit Socket(int fd);
        Socket(const Socket &s);

        Socket& operator =(const Socket &s);

        ~Socket() throw();
    };
}

#endif
