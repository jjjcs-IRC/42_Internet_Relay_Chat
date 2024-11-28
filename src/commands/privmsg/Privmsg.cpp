#include <vector>
#include <sstream>

#include "Privmsg.hpp"

Privmsg::Privmsg() {}

Privmsg::Privmsg(const Privmsg &obj) {}

Privmsg& Privmsg::operator=(const Privmsg &obj)
{
	// this->_type = obj.getType();
	return (*this);
}

Privmsg::~Privmsg() {}

//

void Privmsg::parsing_receiver(tParams &params) //receiver 파싱
{
    std::istringstream ss(params.tokens[1]);
    std::string tmp;
    while (getline(ss, tmp, ',')) //','로 구분
    {
        if (tmp[0] == '#')
            this->v_channel.push_back(tmp);
        else
            this->v_client.push_back(tmp);
    }
}

//client 전송 유효성 검사
int Privmsg::check_client(tParams &params, ClientManager &cl, std::string client)
{
	if (cl.find_client_byNick(client) == NULL)
		return 401;
	return 0;
}

int Privmsg::check_channel(tParams &params, ClientManager &cl, ChannelManager &cn, std::string channel)
{
	Channel *ch = cn.findChannel(channel);
	Client *client = cl.find_client(params.client_fd);
	//채널 이름 형식 검사(413)
	if (!ch->isValideName(channel))
		return 413;

	//채널 존재 검사(403)
	if (ch == NULL)
		return 403;

	//클라이언트가 채널에 가입되어있는지 검사 (404)
	if (ch->findClient(client->get_nickName()) == NULL)
		return 404;

	return 0;
}

void Privmsg::sendMsgToCl(tParams &params, ClientManager &cl, std::string client)
{
	cl.find_client_byNick(client)->set_writeBuf(params.tokens[2] + "\n");
}

void Privmsg::sendMsgToCh(tParams &params, ClientManager &cl, ChannelManager &cn, std::string channel)
{
	std::vector<Client*> list =  cn.findChannel(channel)->getParticipants();

	for (int i = 0; i < list.size(); i++)
		list[i]->set_writeBuf(params.tokens[2] + "\n");
}

int Privmsg::executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn)
{
	Client *executor = cl.find_client(params.client_fd);
	//사용자의 모든 정보가 저장되어 명령어를 사용할 수 있는지 확인
    if (!executor->check_pass_client())
        throw 451;

	//수신자 지정 안됨
	if (params.tokens[1].length() == 0)
		throw 411;

	//보낼 텍스트 없음
	if (params.tokens[2].length() == 0)
		throw 412;

	parsing_receiver(params);

	//단일 상대에게 전송
	if (this->v_client.size() == 1 && this->v_channel.size() == 0)
	{
		if (check_client(params, cl, this->v_client[0]) != 0)
			throw 441;
		sendMsgToCl(params, cl, this->v_client[0]);
	}

	//단일 채널에 전송
	if (this->v_client.size() == 0 && this->v_channel.size() == 1)
	{
		int res = check_channel(params, cl, cn, this->v_channel[0]);
		if (res != 0)
			throw res;
		sendMsgToCh(params, cl, cn, v_channel[0]);
	}

	//다중 대상에게 전송
	//사용자에 전송
	int res = 0;
	for (int i = 0; i < this->v_client.size(); i++)
	{
		if (check_client(params, cl, this->v_client[i]) != 0)
			res = 407;
		else
			sendMsgToCl(params, cl, this->v_client[i]);
	}
	//채널에 전송
	for (int i = 0; i < this->v_channel.size(); i++)
	{
		if (check_channel(params, cl, cn, this->v_channel[i]) != 0)
			res = 407;
		else
			sendMsgToCh(params, cl, cn, this->v_channel[i]);
	}
	throw res;
}