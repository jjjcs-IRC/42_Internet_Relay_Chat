#ifndef CHANNELMANAGER_HPP
#define CHANNELMANAGER_HPP

#include "Channel.hpp"
#include <iostream>
#include <vector>

class ChannelManager
{
private:
    std::vector<Channel*> channels;

    
public:
    ChannelManager();
    ChannelManager(const ChannelManager& other); 
    ChannelManager& operator=(const ChannelManager& other);
    ~ChannelManager();

    Channel* findChannel(const std::string& channelName) const;
    bool addChannel(Channel* newChannel);
    bool deleteChannel(const std::string& channelName);
    void clear();
};

#endif
