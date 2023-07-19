#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <memory>


using boost::asio::ip::tcp;

enum class IPV {
    v4,
    v6
};

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



class TCPServer {
public: 
    TCPServer(IPV _ipVersion, int _port);
    int Run();

private:
    void StartAccept();

private: 
    IPV ipVersion;
    int port;
    boost::asio::io_context ioContext;
    tcp::acceptor acceptor;
    std::vector<TCPConnection::pointer> connections;
};