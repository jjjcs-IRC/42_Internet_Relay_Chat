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
	
	Client *client = cl.find_client(params.client_fd);
	if (client->get_passed() == false) {
		// `USER` 명령어로 사용자 정보를 등록하기 전에 다른 명령어를 사용하려고 하면 이 에러가 발생합니다.
		throw 451;
	}
	
	if (params.tokens[1] == "") {
		// `NICK` 명령어로 전송된 닉네임이 없을 때 발생합니다.
		throw 431;
	}
	else if (cl.find_client_byNick(params.tokens[1]) != NULL) {
		// `NICK` 명령어로 전송된 닉네임이 이미 사용 중일 때 발생합니다.
		throw 433;
	}
	else {
		//클라이언트 닉네임 세팅
		cl.set_nick_client(params.client_fd, params.tokens[1]);
		//클라이언트 등록 완료 문구 전송
		if (client->check_pass_client()) {
			client->set_passed();
			throw 1;
		}
	}
	return 0;
}
