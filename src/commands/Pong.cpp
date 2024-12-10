#include "Pong.hpp"
#include "../server/Server.hpp"

Pong::Pong() {}

Pong::~Pong() {}

Pong &Pong::operator=(const Pong &other) {
	(void)other;
	return (*this);
}

Pong::Pong(const Pong &other) {
	(void)other;
}

int Pong::executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn) {
	Client *client = cl.find_client(params.client_fd);
	// std::cout << "Pong command" << std::endl;

	if (params.tokens.size() < 2) {
		throw 461;
	}

	// std::cout << "Pong command end" << std::endl;
	// 성공 시
	throw 1000;
	return 0;
}