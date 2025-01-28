#include "M3L/Network/Acceptor.hpp"
using TcpAcceptorV4 = m3l::net::Acceptor<
    m3l::net::ip::v4,
    m3l::net::prot::TCP
>;

using TcpSocketV4 = m3l::net::Socket<TcpAcceptorV4::BasicSocketType>;

int main()
{
    TcpAcceptorV4 acceptor = TcpAcceptorV4{ m3l::net::Ip<m3l::net::ip::v4>{"127.0.0.1"}, 0 };
    acceptor.listen();

    TcpSocketV4 socket = TcpSocketV4{ std::move(acceptor.accept()) };
    socket.send({ 1, 8, 5, 4 });
}