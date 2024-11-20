// #ifndef COMMAND_HPP
// # define COMMAND_HPP

// #include <iostream>
// #include <vector>
// #include <string>
// #include "../server/Server.hpp"
// #include "../parser/IrcParser.hpp"
// #include "../parser/IrcType.hpp"

// class Command {
// 	public:
// 		virtual ~Command(){};
// 		virtual int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn) = 0;
// };

// #endif

#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <iostream>
#include <vector>
#include <string>
#include "../parser/IrcType.hpp"  // tParams 정의를 가져오기 위해

// Forward declarations
// class ClientManager;
// class ChannelManager;

// #include "../server/Server.hpp"
#include "../client/ClientManager.hpp"
#include "../channelManager/ChannelManager.hpp"
// #include "../chennel/Channel.hpp"

class Command {
    public:
        virtual ~Command(){};
        virtual int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn) = 0;
};

#endif