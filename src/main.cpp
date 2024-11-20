#include "Server.hpp"

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cout << "Usage: " << argv[0] << " <port> <password>\n";
        return 1;
    }

    Server server(atoi(argv[1]), argv[2]);
    server.start();

	// std::vector<std::string>	params = server.split("PASS 123 NICK hello  USER hi", ' ');

	// for (unsigned long i = 0; i < params.size(); i++)
	// {
	// 	std::cout << params[i] << std::endl;
	// }

    return 0;
}