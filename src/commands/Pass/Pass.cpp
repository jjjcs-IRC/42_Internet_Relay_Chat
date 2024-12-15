#include "Pass.hpp"

Pass::Pass() {}

Pass::~Pass() {}

Pass &Pass::operator=(const Pass &other) {
	(void)other;
	return (*this);
}

Pass::Pass(const Pass &other) {
	(void)other;
}

int Pass::executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn) {
	Client *client = cl.find_client(params.client_fd);

	if (params.tokens.size() < 2) {
		throw 461;
	}
	const std::string inputPassword = params.tokens[1];
	if (client->get_passed()) {// password 통과했는지 확인해주는 함수
		throw 462;
	}
	if (cl.get_server_passwd() != params.tokens[1]) {
		// `PASS` 명령어로 전송된 비밀번호가 서버에 설정된 비밀번호와 일치하지 않을 때 발생합니다.
		throw 464;
	}
	else {
		//클라이언트 pass를 true로 바꿔주기
		client->set_passed();
	}
	return 0;
}