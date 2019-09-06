//
// Created by genkinger on 8/31/19.
//

#ifndef NYARLATHOTEP_SOCKET_HPP
#define NYARLATHOTEP_SOCKET_HPP


#include <Nyarlathotep/Core/Core.hpp>

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

namespace ny::io::net {

    enum class Domain {
        IPV4 = AF_INET,
        UNIX = AF_UNIX
    };

    enum class SocketType {
        RAW = SOCK_RAW,
        DGRAM = SOCK_DGRAM,
        STREAM = SOCK_STREAM
    };

    enum class Protocol {
        UDP = IPPROTO_UDP,
        TCP = IPPROTO_TCP
    };

    class Socket {
        i32 mSocket;
        i32 mSocketDomain;
        i32 mSocketProtocol;
    public:
        Socket(Domain domain, Protocol protocol, SocketType type) {
            mSocket = socket((int) domain, (int) type, (int) protocol);
        }
    };
}


#endif //NYARLATHOTEP_SOCKET_HPP
