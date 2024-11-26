#include "Join.hpp"
#include "../server/Server.hpp"

Join::Join() {}
Join::~Join() {}

Join &Join::operator=(const Join &other) {
	(void)other;
	return (*this);
}

Join::Join(const Join &other) {
	(void)other;
}


int Join::executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn) {
	Channel *channel = cn.findChannel(params.tokens[1]);
	Client *client = cl.find_client(params.client_fd);
	std::string channelName = params.tokens[1]; // # 떼고 채널 이름만 가져옴
	std::string inputPassword = params.tokens.size() > 1 ? params.tokens[2] : ""; // 채널 비밀번호

	std::cout << "Join command::executeCommand" << std::endl;
	// CnManager.joinChannel(channelName); // 채널에 유저 추가

	if (client->get_passed() == false) {
		// `ERR_NOTREGISTERED (451)`
		// `USER` 명령어로 사용자 정보를 등록하기 전에 다른 명령어를 사용하려고 하면 이 에러가 발생합니다.
		// "<client> :You have not registered"
		throw 451;
	}
	
	if(client->check_join_channel() == false) {// 클라이언트의 채널 가입횟수 확인
		//ERR_TOOMANYCHANNELS(405)
		//  "<client> <channel> :You have joined too many channels"
		throw (405);
	}
	else if (channel->getPassword() != inputPassword) { // 채널 비밀번호 확인
		//ERR_BADCHANNELKEY(475)
		// "<client> <channel> :Cannot join channel (+k)"
		throw (475);
	}
	// else if (0) { // 사용자 밴 여부 확인
	// 	//ERR_BANNEDFROMCHAN(474)
	// 	// "<client> <channel> :Cannot join channel (+b)"
	// 	throw (474);
	// }
	else if (channel->isUnderCapacity() == false) { // 채널 내 사용자 수 확인
		//ERR_CHANNELISFULL(471)
		// "<client> <channel> :Cannot join channel (+l)"
		throw (471);

	}
	else {
		if (cn.addChannel(channelName, client)){//채널 존재 여부 확인
		//ERR_NOSUCHCHANNEL(403)
		// "<client> <channel> :No such channel"
			throw (476);
		} 
		// 채널에 유저 추가
		if (channel->addParticipant(client) == false) {
		//ERR_INVITEONLYCHAN(473)
		// "<client> <channel> :Cannot join channel (+i)"
			throw (473);
		}
		//유저에게 채널 추가
		if (client->set_channels(channelName) == false) {
			//위에서 검사하긴 함
			//ERR_TOOMANYCHANNELS(405)
			// "<client> <channel> :You have joined too many channels"
			throw (405);
		}

		/*
		1. RPL_TOPIC (332)
		"<client> <channel> :<topic>" //<channel>현재 주제 를 알려줍니다.


		3.	RPL_NAMREPLY (353) - 채널 멤버 목록
		"<client> <channel> :<nick1> <nick2> <nick3> ... <nickN>" //<channel>의 멤버 목록을 알려줍니다.
		//나누어 보낼지 한번에 보낼지 결정해야함

		4. RPL_ENDOFNAMES (366) - 채널 멤버 목록 끝
		"<client> <channel> :End of /NAMES list." //<channel>의 멤버 목록을 모두 알려준 후 마무리를 알려줍니다.
	*/


		//채널의 모두에게
		// :dan-!d@localhost JOIN #test    ; //dan- is joining the channel #test
		// :<닉네임>!~<유저네임>@<호스트정보> JOIN #channel 
		// :user123123123!~choijimin@crs.42seoul.kr JOIN #jimchoiiii
				// client->set_writeBuf();
		throw (332);
		
	}
}
