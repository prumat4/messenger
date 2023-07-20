#include <../include/tcp_server.hpp>

namespace Networking {
    TCPServer::TCPServer(IPV _ipVersion, int _port) : ipVersion(_ipVersion), port(_port), 
        acceptor(ioContext, tcp::endpoint(_ipVersion == IPV::v4 ? tcp::v4() : tcp::v6(), port))  {}

    int TCPServer::Run() {
        try{
            StartAccept();
            ioContext.run();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }

        return 0;
    }

    void TCPServer::StartAccept() {
        auto connection = TCPConnection::Create(ioContext);
        connections.push_back(connection);

        acceptor.async_accept(connection->getSocket(), [connection, this](const boost::system::error_code& error){
            if(!error)
                connection->Start();

            StartAccept();
        });
    }
}

