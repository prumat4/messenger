#include "../include/tcp_connection.hpp"


namespace Networking {
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
}
