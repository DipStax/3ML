#pragma once

#include "M3L/Network/Ip.hpp"
#include "M3L/Network/CSocket.hpp"

#ifndef M3L_NET_LISTEN_MAX
    #define M3L_NET_LISTEN_MAX 1
#endif

namespace m3l::net
{
    template<IsBaseIp T, m3l::net::prot _T>
    class Acceptor
    {
        public:
            Acceptor(Ip<T> _ip, uint32_t _port = 0)
                : m_socket(c::Socket::create<T, _T>())
            {
            }

            Acceptor(Ip<T> _ip, uint32_t _port = 0)
                : Acceptor()
            {
                connect(_ip, _port)
            }

            bool connect(Ip<T> _ip, uint32_t _port = 0)
            {
                extstd::Expected<sockaddr_in, int> error = c::Socket::bind<Ip<T>>(m_socket, _ip, _port);

                if (error)
                    return false;
                m_addr = error.result();
                if (_port == 0) {

                }
                return true;
            }

            bool listen(int _max = meta::Max<SOMAXCONN, M3L_NET_LISTEN_MAX>::value)
            {
                if (m_addr.sin_port == 0)
                    return false;
                return ::listen(m_socket, _max) == 0;
            }

        private:
            sockaddr_in m_addr;
            WIN_SOCKET m_socket;
    };
}

auto a = m3l::net::Acceptor<
        m3l::net::ip::v4,
        m3l::net::prot::TCP
    >{};