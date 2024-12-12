#include "Join.hpp"

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
	Channel *channel = cn.findChannel(params.tokens[1]);;
	Client *client = cl.find_client(params.client_fd);
	std::string channelName = params.tokens[1]; // # 떼고 채널 이름만 가져옴
	std::string inputPassword = params.tokens.size() > 2 ? params.tokens[2] : ""; // 채널 비밀번호

	if (params.tokens.size() < 2) {
		// `ERR_NEEDMOREPARAMS (461)`
		// `JOIN` 명령어는 적어도 하나의 채널 이름을 인자로 받아야 합니다.
		throw 461;
	}
	if (client->get_passed() == false) {
		// `ERR_NOTREGISTERED (451)`
		// `USER` 명령어로 사용자 정보를 등록하기 전에 다른 명령어를 사용하려고 하면 이 에러가 발생합니다.
		throw 451;
	}
	if (channelName.find(',') != std::string::npos) { // 여러 채널에 입장하고자 할 때
        throw 407; // ERR_BADCHANMASK
    }

	if (channel == NULL) {//채널 존재 여부 확인
		if (!cn.addChannel(channelName, client)){
			throw (476);
		} 
		channel = cn.findChannel(params.tokens[1]);
		if (channel == NULL) {
			throw (403);
		}
	}
	else {
		if(client->check_join_channel() == false) {// 클라이언트의 채널 가입횟수 확인
			throw (405);
		}
		// else if (channel->getPassword() != inputPassword && channel->getPassword() != "") { // 채널 비밀번호 확인
		else if (channel->hasMode('k')) { // 채널 비밀번호 확인
			//   k 모드 아니면 확인 안해도 됨
			if (channel->getPassword() != inputPassword) {
				throw (475);
			}
		}
		else if (channel->isUnderCapacity() == false) { // 채널 내 사용자 수 확인
			throw (471);
		}
	}

	if(channel->findClient(client->get_nickName())){
		// 이미 채널에 클라이언트가 존재하면 끝내기
		return 0;
	}

	// 채널에 유저 추가
	if (channel->addParticipant(client) == false) {
	//ERR_INVITEONLYCHAN(473) // 초대 여부
		throw (473);
	}
	//유저에게 채널 추가
	if (client->set_channels(channelName) == false) {
		// "<client> <channel> :You have joined too many channels"
		throw (405);
	}

	//채널에 메시지 전송
	sendMsgToCh(params, channel, client);
	
	throw (1001);
	return 0;
}

void Join::sendMsgToCh(tParams &params, Channel *channel, Client *sender)
{
	std::vector<Client*> list =  channel->getParticipants();
	std::string join_msg = ":" + sender->get_nickName() + "!" + sender->get_userName() + "@"\
						+ sender->get_clientIp() + " JOIN " + channel->getChannelName() + "\r\n";
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] != sender){
			list[i]->set_writeBuf(join_msg);
		}					
	}
}