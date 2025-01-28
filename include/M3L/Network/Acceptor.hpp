#pragma once

#include "M3L/Network/CSocket.hpp"

#ifndef M3L_NET_LISTEN_MAX
    #define M3L_NET_LISTEN_MAX 1
#endif

namespace m3l::net
{
    template<IsBaseIp T, prot _T>
    class Acceptor : public BasicSocket<T, _T>
    {
        public:
            using BasicSocketType = BasicSocket<T, _T>;

            Acceptor() = default;
            Acceptor(Ip<T> _ip, uint32_t _port = 0);

            bool bind(Ip<T> _ip, uint32_t _port = 0);

            bool listen(int _max = std::max(SOMAXCONN, M3L_NET_LISTEN_MAX));

            BasicSocketType accept();
    };
}