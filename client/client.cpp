#include <iostream>
#include <boost/asio.hpp>
#include <array>

using boost::asio::ip::tcp;

int main() {
    try{
        boost::asio::io_context io_context;

        tcp::resolver resolver (io_context);
        boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "2222");

        tcp::socket socket (io_context);

        // establishes a connection between a socket and one of the endpoints in a sequence of resolved endpoints.
        boost::asio::connect(socket, endpoints);

        for(;;) {
            // listen for message
            std::array<char, 128> buf;
            boost::system::error_code error;

            // reads data from a socket into a buffer and returns the number of bytes read
            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            // end of file
            // In network programming, an "end of file" error typically occurs when the connection has been closed or terminated by the remote endpoint.
            // It indicates that no more data will be received from the socket.
            if(error == boost::asio::error::eof) {
                // clean connection cut off
                break;
            } else if(error) {
                throw boost::system::system_error(error);
            }

            std::cout.write(buf.data(), len);
        }
    } catch (std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    return 0;
}