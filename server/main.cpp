#include "../networking/include/server.hpp"

int main() {
    TCPServer server(IPV::v4, 2222);
    server.Run();
    return 0;
}