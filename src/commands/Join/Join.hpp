#ifndef JOIN_HPP
# define JOIN_HPP

#include "../Command.hpp"

class Join : public Command {
    public:
        Join();
        ~Join();
        virtual int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn);

    private:
        Join(const Join &other);
        Join& operator=(const Join &other);
        void sendMsgToCh(tParams &params, Channel *channel, Client *client);
};

#endif