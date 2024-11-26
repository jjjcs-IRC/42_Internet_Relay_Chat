#ifndef TOPIC_HPP
#define TOPIC_HPP

#include "../Command.hpp"

class Topic : public Command
{
private:
    Topic(const Topic &obj);
    Topic& operator=(const Topic &obj);
public:
    Topic();
    virtual ~Topic();
    int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn);
};

#endif