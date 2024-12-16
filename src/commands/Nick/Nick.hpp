#ifndef NICK_HPP
# define NICK_HPP

#include "../Command.hpp"

class Nick : public Command {
    public:
        Nick();
        ~Nick();
        int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn);

    private:
        Nick(const Nick &other);
        Nick& operator=(const Nick &other);
        bool check_nick(std::string nick);
        void send_nick_ch_msg(tParams &params, ClientManager &cl, ChannelManager &cn, std::string msg);
};

#endif