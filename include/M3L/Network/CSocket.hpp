#pragma once

#include <string>
#include <cstdint>

#include <WinSock2.h>

#include "M3L/Network/Protocol.hpp"
#include "M3L/Network/meta.hpp"
#include "Tool/Expected.hpp"

namespace m3l::net
{
    /// @brief C++ to C binding namespace.
    namespace c
    {
        /// @brief C++ binding struct for file descriptor scoket.
        struct Socket
        {
            template<IsBaseIp T, m3l::net::prot _T>
            [[nodiscard]] static constexpr WIN_SOCKET create();

            /// @brief C++ binding to the C function socket.
            /// @param _dom The familly of protocol uesd.
            /// @param _type The type of logique for communication.
            /// @param _proto Specific protocol type from the protocol familly.
            /// @return The file descriptor created.
            [[nodiscard]] static constexpr WIN_SOCKET create(int _dom, int _type, int _proto);

            template<IsIpFormat T>
            static extstd::Expected<sockaddr_in, int> bind(WIN_SOCKET _socket, const T &_ip, uint32_t _port);

            /// @brief Set a file descriptor as blocking or not.
            /// @param _socket File descriptor to modify
            /// @param _block If true the file descriptor will be blocking otherwise it will be non-blocking.
            /// @return True if the modification of the file descriptor succed otherwise false.
            static bool blocking(WIN_SOCKET _socket, bool _block);

            /// @brief C++ binding to the C function close.
            /// @param _socket File descriptor to close.
            /// @return True if the close function succed.
            static bool close(WIN_SOCKET _socket);

        };
    }
}