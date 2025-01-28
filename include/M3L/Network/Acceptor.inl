#include "M3L/Network/Acceptor.hpp"

namespace m3l::net
{
    template<IsBaseIp T, prot _T>
    Acceptor<T, _T>::Acceptor(Ip<T> _ip, uint32_t _port = 0)
        : Acceptor<T, _T>()
    {
        bind(_ip, _port)
    }

    template<IsBaseIp T, prot _T>
    bool Acceptor<T, _T>::bind(Ip<T> _ip, uint32_t _port = 0)
    {
        extstd::Expected<sockaddr_in, int> error = c::Socket::bind<Ip<T>>(m_socket, _ip, _port);

        if (error)
            return false;
        m_addr = error.result();
        retreive_port();
        return true;
    }

    template<IsBaseIp T, prot _T>
    bool Acceptor<T, _T>::listen(int _max = std::max(SOMAXCONN, M3L_NET_LISTEN_MAX))
    {
        if (m_addr.sin_port == 0)
            return false;
        return ::listen(m_socket, _max) == 0;
    }

    template<IsBaseIp T, prot _T>
    Acceptor<T, _T>::BasicSocketType Acceptor<T, _T>::accept()
    {
        sockaddr_in addr{};
        int len = sizeof(sockaddr_in);
        WIN_SOCKET socket = ::accept(m_socket, &addr, &len);

        return BasicSocketType{ socket, addr };
    }
}