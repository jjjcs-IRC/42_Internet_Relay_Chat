#include "User.hpp"

User::User() {}

User::~User() {}

User &User::operator=(const User &other) {
	(void)other;
	return (*this);
}
User::User(const User &other) {
	(void)other;
}

int User::executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn) {
	(void)cn;
	
	Client *client = cl.find_client(params.client_fd);
	if (client->get_passed() == false) {
		return 0;
	}
	else if(params.tokens.size() < 5){ //매개변수가 충분하지 않음
		throw 461;
	}
	else if (client->get_realName().size() > 0 || client->get_realName().size() > 0) {//   "You may not reregister" 재등록 하려고 할 때
		throw 462;
	}
	else {
		client->set_userName(params.tokens[1]);
		client->set_realName(params.tokens[4]);
		//클라이언트 등록 완료 문구 전송
		if (client->check_pass_client()) {
			client->set_passed();
			throw 1;
		}
		return 0;
	}
}