#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <iostream>
#include <vector>
#include <string>

class Command {
	public:
		virtual ~Command();
		virtual int executeCommand(std::vector<std::string> &messages, ClientManager &cl, ChannelManager &cn) = 0;
	protected:
		std::string _type;
		//클라매니저
		//채널매니저
};


#endif