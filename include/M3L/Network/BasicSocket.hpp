#pragma once

#include "M3L/Network/Ip.hpp"

namespace m3l::net
{
    template<IsBaseIp T, prot _T>
    class BasicSocket
    {
        public:
            using IpVersion = T;
            constexpr prot Protocol = _T;

            [[nodiscard]] bool is_open() const;

            void close();

        protected:
            BasicSocket() = default;
            BasicSocket(const BasicSocket &&_bs) noexcept;
            BasicSocket(WIN_SOCKET _socket, sockaddr_in _addr);
            void retreive_port();

            sockaddr_in m_addr{};
            WIN_SOCKET m_socket;
    };
}

#include "M3L/Network/BasicSocket.inl"