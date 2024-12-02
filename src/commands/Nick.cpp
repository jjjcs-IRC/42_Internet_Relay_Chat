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
	
	// std::cout << "Nick executeCommand" << std::endl;
	Client *client = cl.find_client(params.client_fd);
	std::string isFirst = client->get_nickName();
	if (client->get_passed() == false) {
		// `USER` 명령어로 사용자 정보를 등록하기 전에 다른 명령어를 사용하려고 하면 이 에러가 발생합니다.
		std::cout <<"PASS 를 먼저 입력해야함"<<std::endl;
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
	//클라이언트 닉네임 세팅
	// if (!cl.set_nick_client(params.client_fd, params.tokens[1])) {
	// 	// `NICK` 명령어로 전송된 닉네임이 서버에서 허용되지 않을 때 발생합니다.
	// 	throw 432;
	// }
	if (check_nick(params.tokens[1]) == false) {
		// `NICK` 명령어로 전송된 닉네임이 서버에서 허용되지 않을 때 발생합니다.
		throw 432;
	}
	//클라이언트 등록 완료 문구 전송
	// if (client->check_pass_client() ) {
	if (client->check_pass_client() && isFirst.size() == 0) {
		client->set_passed();
		cl.set_nick_client(params.client_fd, params.tokens[1]);
		throw 1;
	}
	cl.set_nick_client(params.client_fd, params.tokens[1]);
	if (client->check_pass_client()) //  닉네임 변경 성공 메세지 전송
		client->set_writeBuf(":" + client->get_nickName() 
								+"!~" +client->get_userName() 
								+ "@" + client->get_clientIp()
								+ " NICK " + params.tokens[1] 
								+ "\r\n");
	return 0;
}


bool Nick::check_nick(std::string nick) {
	if (nick.size() > 9) {
		return false;
	}
    if (nick[0] == '#' || nick[0] == '&')
        return (false);
	return true;
}