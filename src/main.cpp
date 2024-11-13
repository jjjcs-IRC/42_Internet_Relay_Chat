#include "Server.hpp"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "Usage: " << argv[0] << " <port>\n";
        return 1;
    }

    Server server;
    server.start(atoi(argv[1]));

    return 0;
}