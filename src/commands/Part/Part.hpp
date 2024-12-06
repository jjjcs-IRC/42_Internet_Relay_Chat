#ifndef PART_HPP
#define PART_HPP

#include "../Command.hpp"

class Part : public Command
{
private:
    Part(const Part &obj);
    Part& operator=(const Part &obj);
    //
    std::vector<std::string> v_channel;
public:
    Part();
    virtual ~Part();
    int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn);
};

#endif