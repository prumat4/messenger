#include "server.hpp"

TCPServer::TCPServer(IPV _ipVersion, int _port) : ipVersion(_ipVersion), port(_port), 
    acceptor(ioContext, tcp::endpoint(_ipVersion == IPV::v4 ? tcp::v4() : tcp::v6(), port))  {

    }

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

TCPConnection::TCPConnection(boost::asio::io_context& _ioContext) : socket(_ioContext) {}

tcp::socket &TCPConnection::getSocket() {
    return socket;
}

void TCPConnection::Start() {
    auto sharedThis = shared_from_this();

    boost::asio::async_write(socket, boost::asio::buffer(message), [sharedThis, this](const boost::system::error_code& error, size_t bytesTransferred){
        if(error)
            std::cout << "Failed to send message!\n";
        else 
            std::cout << "Sent " << bytesTransferred << " bytes of data\n";
    }); 

    boost::asio::streambuf buffer;
    
    socket.async_receive(buffer.prepare(512), [this](const boost::system::error_code& error, size_t bytesTransferred){
        if(error == boost::asio::error::eof)
            std::cout << "Client disconnected properly!\n";
        else if(error)
            std::cout << "Client disconnected in bad way!\n";
    });
}

TCPConnection::pointer TCPConnection::Create(boost::asio::io_context& _ioContext) {
    return pointer(new TCPConnection(_ioContext));
}

int main() {
    TCPServer server(IPV::v4, 2222);
    server.Run();

    return 0;
}