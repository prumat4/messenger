#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <string>
// #include <vector>
#include <memory>


namespace Networking {
    using boost::asio::ip::tcp;
    
    class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
    public:
        using pointer = std::shared_ptr<TCPConnection>;
        
        static pointer Create(boost::asio::io_context& _ioContext);
        tcp::socket& getSocket();
        void Start();

    private:
        explicit TCPConnection(boost::asio::io_context& _ioContext);

    private:
        tcp::socket socket;
        std::string message {"Hello, client!"};
    };
}