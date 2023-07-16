#include <iostream>
#include <boost/asio.hpp>
#include <string>

#define PORT_NUMBER 2222

using boost::asio::ip::tcp;

int main() {
    try {
        std::cout << "Accepting connections on port" << PORT_NUMBER << "...\n";

        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), PORT_NUMBER));

        for (;;) {
            boost::system::error_code error;

            tcp::socket socket(io_context);

            acceptor.accept(socket);

            std::cout << "Client connected! Waiting for message...\n";

            std::string buf; 
            buf.resize(128);

            socket.read_some(boost::asio::buffer(buf), error);

            if (error)
                throw boost::system::system_error(error);

            std::cout << "Received message from client: " << buf << std::endl;
            boost::asio::write(socket, boost::asio::buffer(buf), error);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
