
#ifndef USER_HPP
# define USER_HPP

#include "../parser/IrcType.hpp"  // tParams 정의를 가져오기 위해
#include "Command.hpp"

class User : public Command {
    public:
        User();
        ~User();
        virtual int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn);

    private:
        User(const User &other);
        User& operator=(const User &other);
};

#endif