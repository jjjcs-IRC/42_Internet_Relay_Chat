#ifndef INVITE_CLASS
#define INVITE_CLASS

#include "../parser/IrcType.hpp"
#include "Command.hpp"

class Invite
{
private:
    Invite(const Invite &obj);
    Invite& operator=(const Invite &obj);
public:
    Invite();
    ~Invite();
    virtual int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn);
};

#endif