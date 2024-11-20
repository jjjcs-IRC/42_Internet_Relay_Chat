#include "User.hpp"

User::User() {
	_type = "USER";
}

User::~User() {}

User *User::operator=(const User &other) {
	(void)other;
	return (this);
}
User::User(const User &other) {
	(void)other;
}

int User::executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn) {

	Client *client = cl.find_client(params.client_fd);
	if (client->get_passed() == false) {
		// `ERR_NOTREGISTERED (451)`
		// `USER` 명령어로 사용자 정보를 등록하기 전에 다른 명령어를 사용하려고 하면 이 에러가 발생합니다.
		// "<client> :You have not registered"
		return 451;
	}
	else if(params.tokens.size() < 5){ //매개변수가 충분하지 않음
		// ERR_NEEDMOREPARAMS (461)
		// "<client> <command> :Not enough parameters"
		return 461;
	}
	else if (client->get_realName().size() > 0 || client->get_nickName().size() > 0) {
		// ERR_ALREADYREGISTERED (462)
		//   "<client> :You may not reregister"
		return 462;
	}
	else {
		//클라이언트 user를 true로 바꿔주기
		;
		return 0;
	}
}