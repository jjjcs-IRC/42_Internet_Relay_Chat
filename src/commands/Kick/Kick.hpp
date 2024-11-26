#ifndef KICK_HPP
#define KICK_HPP

#include "../Command.hpp"

class Kick : public Command
{
private:
    Kick(const Kick &obj);
    Kick& operator=(const Kick &obj);
public:
    Kick();
    virtual ~Kick();
    int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn);
};

#endif