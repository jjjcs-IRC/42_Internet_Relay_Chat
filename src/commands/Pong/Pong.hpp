#ifndef PONG_HPP
# define PONG_HPP
#include "../Command.hpp"


class Pong : public Command {

	public :
		Pong();
		~Pong();
		int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn);

	private :
		Pong(const Pong &other);
		Pong& operator=(const Pong &other);

};


#endif