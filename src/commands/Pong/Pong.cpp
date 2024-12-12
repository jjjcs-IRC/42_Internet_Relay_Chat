#include "Pong.hpp"

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

	if (params.tokens.size() < 2) {
		throw 461;
	}
	// 성공 시
	throw 1000;
	return 0;
}