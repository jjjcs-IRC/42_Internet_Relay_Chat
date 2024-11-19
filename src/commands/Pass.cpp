// #ifndef PASS_HPP
// # define PASS_HPP

#include "../Server.hpp"
#include "Command.hpp"




class Pass : public Command {

	public :
		Pass();
		~Pass();
		int executeCommand(t_params &params, ClientManager &cl, ChannelManager &cn);

	private :
		Pass(const Pass &other);
		Pass* operator=(const Pass &other);

};


// #endif
Pass::Pass() {
	_type = "PASS";
}

Pass::~Pass() {}

int Pass::executeCommand(t_params &params, ClientManager &cl, ChannelManager &cn) {
	Client *client = cl.find_client(params.client_fd);
	if (client->get_passed()) {// password 통과했는지 확인해주는 함수
	// `ERR_NEEDMOREPARAMS (461)`
	//클라이언트가 등록을 완료한 후에 다시 `PASS`(비밀번호) 또는 `USER`(사용자 정보) 명령어를 재전송하려고 하면 이 에러가 발생합니다.
	//   "<client> <command> :Not enough parameters"
	return 461;
	}

	params.tokens[1].erase(std::remove(params.tokens[1].begin(), params.tokens[1].end(), '\n'), params.tokens[1].end());
	if (params.password != params.tokens[1]) {
			// `ERR_PASSWDMISMATCH (464)`
	// `PASS` 명령어로 전송된 비밀번호가 서버에 설정된 비밀번호와 일치하지 않을 때 발생합니다.
		return 464;
	}
	else {
	//클라이언트 pass를 true로 바꿔주기
	client->set_passed();
		return 0;
	}
}