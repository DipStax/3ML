#pragma once

#include "M3L/Network/BasicSocket.hpp"

namespace m3l::net
{
    namespace imp
    {
        template<IsBaseIp T, prot _T>
        struct Socket;

        template<IsBaseIp T>
        struct Socket<T, m3l::net::prot::UDP> : public BaseSocket<T, m3l::net::prot::UDP>
        {
            void send(const std::vector<uint8_t> _data);
            std::vector<uint8_t> receive(size_t _size = std::numeric_limit<size_t>::max());
        };

        template<IsBaseIp T>
        struct Socket<T, m3l::net::prot::TCP> : public BaseSocket<T, m3l::net::prot::TCP>
        {
            void send(const std::vector<uint8_t> _data);
            std::vector<uint8_t> receive(size_t _size = std::numeric_limit<size_t>::max());
        };
    }

    template<IsBaseSocket T>
    class Socket : public Socket<T::IpVersion, T::Protocol> {};

    template<IsBaseIp T, prot _T>
    class Socket : public imp::Socket<T, _T>
    {
        public:
            Socket() = default;
            Socket(const Socket<T, _T> &&_socket) noexcept;
            Socket(const BaseSocket<T, _T> &&_bs) noexcept;
    
            void connect(const Ip<T> &_ip, uint32_t _port);
    };
}