#include "Pass.hpp"
#include "../server/Server.hpp"

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
	std::cout << "Pass command" << std::endl;
	// params.tokens[1].erase(std::remove(params.tokens[1].begin(), params.tokens[1].end(), '\n'), params.tokens[1].end());
	const std::string inputPassword = params.tokens[1];
		// `ERR_NEEDMOREPARAMS (461)`
		//   "<client> <command> :Not enough parameters"
	if (client->get_passed()) {// password 통과했는지 확인해주는 함수
		//클라이언트가 등록을 완료한 후에 다시 `PASS`(비밀번호) 또는 `USER`(사용자 정보) 명령어를 재전송하려고 하면 이 에러가 발생합니다.
		throw 462;
	}
	if (cl.get_server_passwd() != params.tokens[1]) {
		// `ERR_PASSWDMISMATCH (464)`
		// `PASS` 명령어로 전송된 비밀번호가 서버에 설정된 비밀번호와 일치하지 않을 때 발생합니다.
		throw 464;
	}
	else {
		//클라이언트 pass를 true로 바꿔주기
		client->set_passed();
		throw 0;
	}
}