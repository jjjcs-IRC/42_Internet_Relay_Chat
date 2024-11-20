#ifndef PASS_HPP
# define PASS_HPP
#include "../parser/IrcType.hpp"  // tParams 정의를 가져오기 위해
#include "Command.hpp"
// class Command;
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