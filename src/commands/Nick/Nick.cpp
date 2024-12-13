#include "Nick.hpp"

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
	std::string isFirst = client->get_nickName();
	if (client->get_passed() == false) {
		// `USER` 명령어로 사용자 정보를 등록하기 전에 다른 명령어를 사용하려고 하면 이 에러가 발생합니다.
		// throw 451;
		return 0;
	}
	
	if (params.tokens.size() < 2) {
		// `NICK` 명령어로 전송된 닉네임이 없을 때 발생합니다.
		throw 431;
	}
	else if (cl.find_client_byNick(params.tokens[1]) != NULL) {
		// `NICK` 명령어로 전송된 닉네임이 이미 사용 중일 때 발생합니다.
		throw 433;
	}
	if (check_nick(params.tokens[1]) == false) {
		// `NICK` 명령어로 전송된 닉네임이 서버에서 허용되지 않을 때 발생합니다.
		throw 432;
	}
	//클라이언트 등록 완료 문구 전송
	std::string pre_nickName = client->get_nickName();
	cl.set_nick_client(params.client_fd, params.tokens[1]);
	if (client->get_userName().size() != 0 && isFirst.size() == 0) { 
		client->set_passed();
		throw 1;
	}
	 // 닉네임 변경
	if (isFirst.size() != 0) //  닉네임 변경 성공 메세지 전송
	{
		std::string msg = ":" + pre_nickName +"!" +client->get_userName() + "@" + client->get_clientIp() \
								+ " NICK :" + params.tokens[1] + "\r\n";
		send_nick_ch_msg(params, cl, cn, msg);
	}
	return 0;
}

bool Nick::check_nick(std::string nick) {
	//최대 길이 제한 (9자 초과 불가)
	if (nick.size() > 9) {
		return false;
	}

	//첫 글자는 알파벳(a-z, A-Z), 숫자(0-9), 또는 특정 특수문자(~, -, _, ^)
    if (nick[0] != '~' && nick[0] != '-' && nick[0] != '_' && nick[0] != '^' && !isalnum(nick[0]))
		return false;

	//닉네임에 공백, @, !, #, :, , 등 특정 특수 문자 포함 불가
	for (int i = 0; i < nick.size(); i++)
	{
		if (nick[i] == ' ')
			return (false);
		if (nick[i] == '@')
			return (false);
		if (i != 0 && nick[i] == '!')
			return (false);
		if (nick[i] == '#')
			return (false);
		if (nick[i] == ':')
			return (false);
		if (nick[i] == ',')
			return (false);
		if (nick[i] == '\n')
			return (false);
		// if (nick[i] == '*')
		// 	return (false);
		// if (nick[i] == '?')
		// 	return (false);
		// if (i != 0 && nick[i] == '!')
		// 	return (false);
		// if (nick[i] == '.')
		// 	return (false);
	}
	return true;
}

void Nick::send_nick_ch_msg(tParams &params, ClientManager &cl, ChannelManager &cn, std::string msg)
{
	Client *client = cl.find_client(params.client_fd);

	std::vector<std::string> channel_list = client->get_channels();
	for (int i = 0; i < channel_list.size(); i++)
	{
		Channel *channel = cn.findChannel(channel_list[i]);
		std::vector<Client*> client_list = channel->getParticipants();

		for (int j = 0; j < client_list.size(); j++)
			client_list[j]->set_writeBuf(msg);
	}
}