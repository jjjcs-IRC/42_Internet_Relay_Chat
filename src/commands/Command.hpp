#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <iostream>
#include <vector>
#include <string>
#include "Server.hpp"

class Command {
	public:
		virtual ~Command(){};
		virtual int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn) = 0;
};

#endif