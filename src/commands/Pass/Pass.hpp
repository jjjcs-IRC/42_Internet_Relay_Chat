#ifndef PASS_HPP
# define PASS_HPP

#include "../Command.hpp"

class Pass : public Command {

	public :
		Pass();
		~Pass();
		int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn);

	private :
		Pass(const Pass &other);
		Pass& operator=(const Pass &other);

};


#endif