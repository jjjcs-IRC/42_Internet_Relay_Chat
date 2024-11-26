// #ifndef NICK_HPP
// # define NICK_HPP

// #include "Command.hpp"
// // #include "../server/Server.hpp"
// // #include "../parser/IrcParser.hpp" 
// class ClientManager;
// class ChannelManager;
// // struct tParams;

// class Nick : public Command {

// 	public :
// 		Nick();
// 		~Nick();
// 		int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn);

// 	private :
// 		Nick(const Nick &other);
// 		Nick* operator=(const Nick &other);
// 		// bool 		nick_check(std::string nick);
		
// };

// #endif

#ifndef NICK_HPP
# define NICK_HPP

#include "../parser/IrcType.hpp"  // tParams 정의를 가져오기 위해
#include "Command.hpp"

class Nick : public Command {
    public:
        Nick();
        ~Nick();
        int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn);

    private:
        Nick(const Nick &other);
        Nick& operator=(const Nick &other);
};

#endif