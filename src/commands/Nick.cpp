#include "Nick.hpp"
#include "../server/Server.hpp"


Nick::Nick() {}

Nick::~Nick() {}

Nick &Nick::operator=(const Nick &other) {
	(void)other;
	return (*this);
}
Nick::Nick(const Nick &other) {
	(void)other;
}

int Nick::executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn) {
	// ChannelManager CnManager;
	
	Client *client = cl.find_client(params.client_fd);

	if (params.tokens[1] == "") {
		// `ERR_NONICKNAMEGIVEN (431)`
		// `NICK` 명령어로 전송된 닉네임이 없을 때 발생합니다.
		// "<client> :No nickname given"
		return 431;
	}
// else if (nick_check(params.tokens[1]) == false) {
// 		// `ERR_ERRONEUSNICKNAME (432)`
// 		// `NICK` 명령어로 전송된 닉네임이 잘못되었을 때 발생합니다.
// 		// "<client> <nick> :Erroneous nickname"
// 		return 432;
// 	}
	else if (cl.find_client_byNick(params.tokens[1]) != NULL) {
		// `ERR_NICKNAMEINUSE (433)`
		// `NICK` 명령어로 전송된 닉네임이 이미 사용 중일 때 발생합니다.
		// "<client> <nick> :Nickname is already in use"
		return 433;
	}
	else {
		//클라이언트 닉네임 세팅
		client->set_nickName(params.tokens[1]);

		if (client->get_passed()) {
			client->set_passed();
			throw 1;
		}
		return 0;
	}

}
