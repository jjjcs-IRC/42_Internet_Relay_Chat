#ifndef PRIVMSG_HPP
#define PRIVMSG_HPP

#include "../Command.hpp"

class Privmsg : public Command
{
private:
	Privmsg(const Privmsg &obj);
	Privmsg& operator=(const Privmsg &obj);
	//
	std::vector<std::string> v_client;
	std::vector<std::string> v_channel;
	//
	void parsing_receiver(tParams &params);
	int check_client(tParams &params, ClientManager &cl, std::string channel);
	int check_channel(tParams &params, ClientManager &cl, ChannelManager &cn, std::string channel);
	void sendMsgToCl(tParams &params, ClientManager &cl, std::string client);
	void sendMsgToCls(tParams &params, ClientManager &cl, std::string client);
	void sendMsgToCh(tParams &params, ClientManager &cl, ChannelManager &cn, std::string channel);
	void sendMsgToChs(tParams &params, ClientManager &cl, ChannelManager &cn, std::string channel);
public:
	Privmsg();
	virtual ~Privmsg();
	int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn);
};

#endif