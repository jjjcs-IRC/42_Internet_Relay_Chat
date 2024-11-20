#ifndef NICK_HPP
# define NICK_HPP

#include "Command.hpp"

class Nick : public Command {

	public :
		Nick();
		~Nick();
		int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn);

	private :
		Nick(const Nick &other);
		Nick* operator=(const Nick &other);
		bool 		nick_check(std::string nick);
		
};

#endif