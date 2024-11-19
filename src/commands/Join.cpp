// #ifndef JOIN_HPP
// # define JOIN_HPP

#include "Command.hpp"
#include "../Server.hpp"

class Join : public Command {

	public :
		Join();
		~Join();
		int executeCommand(t_params &params, ClientManager &cl, ChannelManager &cn);

	private :
		Join(const Join &other);
		Join* operator=(const Join &other);

		

};


// #endif

Join::Join() {
	_type = "JOIN";
}

Join::~Join() {}

int Join::executeCommand(t_params &params, ClientManager &cl, ChannelManager &cn) {
	// ChannelManager CnManager;

	std::string channelName = params.tokens[1]; // # 떼고 채널 이름만 가져옴
	// CnManager.joinChannel(channelName); // 채널에 유저 추가
	if (1){//채널 존재 여부 확인
		//ERR_NOSUCHCHANNEL(403)
		// "<client> <channel> :No such channel"
		return (403);
	} 
	else if(2) {// 클라이언트의 채널 가입횟수 확인
		//ERR_TOOMANYCHANNELS(405)
		//  "<client> <channel> :You have joined too many channels"
		return (405);
	}
	else if (3) { // 채널 비밀번호 확인
		//ERR_BADCHANNELKEY(475)
		// "<client> <channel> :Cannot join channel (+k)"
		return (475);
	}
	else if (4) { // 사용자 밴 여부 확인
		//ERR_BANNEDFROMCHAN(474)
		// "<client> <channel> :Cannot join channel (+b)"
		return (474);
	}
	else if (5) { // 채널 내 사용자 수 확인
		//ERR_CHANNELISFULL(471)
		// "<client> <channel> :Cannot join channel (+l)"
		return (471);

	}
	else if (6) { // 채널 초대 모드 확인
		//ERR_INVITEONLYCHAN(473)
		// "<client> <channel> :Cannot join channel (+i)"
		return (473);
	}
	else {
		//채널에 유저 추가
		// CnManager.joinChannel(channelName);
		//유저에게 채널 추가
		// cl.add_channel(channelName);
		return (0);

	}
}
