#include "Join.hpp"

Join::Join() {}
Join::~Join() {}

Join *Join::operator=(const Join &other) {
	(void)other;
	return (this);
}

Join::Join(const Join &other) {
	(void)other;
}


int Join::executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn) {
	Channel *channel = cn.findChannel(params.tokens[1]);
	Client *client = cl.find_client(params.client_fd);
	std::string channelName = params.tokens[1]; // # 떼고 채널 이름만 가져옴
	std::string inputPassword = params.tokens.size() > 1 ? params.tokens[2] : ""; // 채널 비밀번호

	// CnManager.joinChannel(channelName); // 채널에 유저 추가
	if (cn.findChannel(channelName)){//채널 존재 여부 확인
		//ERR_NOSUCHCHANNEL(403)
		// "<client> <channel> :No such channel"
		return (403);
	} 
	else if(client->check_join_channel() == false) {// 클라이언트의 채널 가입횟수 확인
		//ERR_TOOMANYCHANNELS(405)
		//  "<client> <channel> :You have joined too many channels"
		return (405);
	}
	else if (channel->getPassword() != inputPassword) { // 채널 비밀번호 확인
		//ERR_BADCHANNELKEY(475)
		// "<client> <channel> :Cannot join channel (+k)"
		return (475);
	}
	else if (0) { // 사용자 밴 여부 확인
		//ERR_BANNEDFROMCHAN(474)
		// "<client> <channel> :Cannot join channel (+b)"
		return (474);
	}
	else if (channel->isUnderCapacity() == false) { // 채널 내 사용자 수 확인
		//ERR_CHANNELISFULL(471)
		// "<client> <channel> :Cannot join channel (+l)"
		return (471);

	}
	else {
		// 채널에 유저 추가
		if (channel->addParticipant(client) == false) {
		//ERR_INVITEONLYCHAN(473)
		// "<client> <channel> :Cannot join channel (+i)"
			return (473);
		}
		//유저에게 채널 추가
		if (client->set_channels(channelName) == false) {
			//위에서 검사하긴 함
			//ERR_TOOMANYCHANNELS(405)
			// "<client> <channel> :You have joined too many channels"
			return (405);
		}
		return (0);

	}
}
