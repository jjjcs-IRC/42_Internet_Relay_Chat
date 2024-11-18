#ifndef PRIVMSG_HPP
#define PRIVMSG_HPP

#include "../Command.hpp"

class Privmsg : public Command
{
private:
	Privmsg(const Privmsg &obj);
	Privmsg& operator=(const Privmsg &obj);
public:
	Privmsg();
	virtual ~Privmsg();
	int executeCommand(std::vector<std::string> &msg, ClientManager &cl, ChannelManager &cn);
	int sendMsg();
};

#endif