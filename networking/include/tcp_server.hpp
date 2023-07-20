#pragma once

#include "./tcp_connection.hpp"

using boost::asio::ip::tcp;

namespace Networking {
        enum class IPV {
            v4,
            v6
        };
    
    class TCPServer {
    public: 
        TCPServer(IPV _ipVersion, int _port);
        int Run();
        
        template <typename T>
        void WriteToConnection(int connectionIndex, const T& message);
    
        // listen callbacks 
    
    private:
        void StartAccept();
    
    private: 
        IPV ipVersion;
        int port;
        
        boost::asio::io_context ioContext;
        tcp::acceptor acceptor;
        
        std::vector<TCPConnection::pointer> connections;
    };
}