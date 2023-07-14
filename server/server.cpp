#include <iostream>
#include <boost/asio.hpp>

#define PORT_NUMBER 2222

using boost::asio::ip::tcp;

int main() {
    try{
        std::cout << "Accepting connections on port " << PORT_NUMBER << "...\n";
        
        // create context for I/O functionality
        boost::asio::io_context io_context;
        
        // create acceptor, which will listen on some socket on specific endpoint 
        // with io_context and endpoint(IPv4, PORT_NUMBER)
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), PORT_NUMBER));
        
        // for while
        for(;;) {
        
            // create a socket which is enpoint for sending a receving data
            tcp::socket socket(io_context);
        
            // accept connection of client on socket
            // accept() block until client is connected
            acceptor.accept(socket);

            std::cout << "Client connected! Sending message...\n";
            std::string message = "Hello, client";
            boost::system::error_code error;

            //write() writes data to a socket using buffer
            boost::asio::write(socket, boost::asio::buffer(message), error);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}