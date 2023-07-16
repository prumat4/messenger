#include <iostream>
#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context);
        boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "2222");

        tcp::socket socket(io_context);

        boost::asio::connect(socket, endpoints);

        std::string message; 
        boost::system::error_code error;
        
        std::cout << "Give me your message: ";
        std::getline(std::cin, message);
        
        boost::asio::write(socket, boost::asio::buffer(message), error);
        
        if (error)
            throw boost::system::system_error(error);
        
        std::string response;
        response.resize(128);
        
        socket.read_some(boost::asio::buffer(response), error);
        
        if (error)
            throw boost::system::system_error(error);
        
        std::cout << "Response from server: " << response << std::endl;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}