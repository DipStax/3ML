#include <expected>

#include "M3L/Network/CSocket.hpp"

namespace m3l::net::c
{
    template<IsBaseIp T, m3l::net::prot _T>
    constexpr WIN_SOCKET Socket::create()
    {
        if constexpr (_T == m3l::net::prot::TCP) {
            return m3l::net::c::Socket::create(T::familly, SOCK_STREAM, IPPROTO_TCP);
        } else if constexpr (_T == m3l::net::prot::UDP) {
            return m3l::net::c::Socket::create(T::familly, SOCK_DGRAM, IPPROTO_UDP);
        } else constexpr {
            static_assert(false, "Unknow protocol");
        }
    }

    template<IsIpFormat T>
    extstd::Expected<sockaddr_in, int> Socket::bind(WIN_SOCKET _socket, const T &_ip, uint32_t _port)
    {
        sockaddr_in addr{};
        int err = 0;

        addr.sin_family = T::familly;
        addr.sin_addr.s_addr = inet_addr(_ip.str().c_str());
        addr.sin_port = htons(_port);
        err = ::bind(_socket, &addr, sizeof(sockaddr_in));

        if (err == 0)
            return extstd::Expected(addr);
        return extstd::Expected(err);
    }
}