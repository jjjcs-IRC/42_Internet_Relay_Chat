#ifndef NICK_HPP
# define NICK_HPP

#include "Command.hpp"

class Nick : public Command {

	public :
		Nick();
		~Nick();
		int executeCommand(std::vector<std::string> &messages, ClientManager &cl, ChannelManager &cn);

	private :
		Nick(const Nick &other);
		Nick* operator=(const Nick &other);
		bool 		nick_check(std::string nick);
		
};

Nick::Nick() {
	_type = "NICK";
}

Nick::~Nick() {}

int Nick::executeCommand(std::vector<std::string> &messages, ClientManager &cl, ChannelManager &cn) {
	// ChannelManager CnManager;

	if (messages[1] == "") {
		// `ERR_NONICKNAMEGIVEN (431)`
		// `NICK` 명령어로 전송된 닉네임이 없을 때 발생합니다.
		// "<client> :No nickname given"
		return 431;
	}
else if (nick_check(messages[1]) == false) {
		// `ERR_ERRONEUSNICKNAME (432)`
		// `NICK` 명령어로 전송된 닉네임이 잘못되었을 때 발생합니다.
		// "<client> <nick> :Erroneous nickname"
		return 432;
	}
	else if (cl.get_nickName()) {
		// `ERR_NICKNAMEINUSE (433)`
		// `NICK` 명령어로 전송된 닉네임이 이미 사용 중일 때 발생합니다.
		// "<client> <nick> :Nickname is already in use"
		return 433;
	}
	else {
		//클라이언트 닉네임 세팅
		client.set_nickName(messages[1]);
		return 0;
	}

}

#endif