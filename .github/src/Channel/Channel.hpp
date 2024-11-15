#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include "Client.hpp" 

class Channel
{
private:
    std::string channelName;
    std::string password;
    std::string topic;
    Client* leader;
    std::string mode;
    std::vector<Client*> participants;
public:
    Channel(std::string const &channelName);
	Channel(Channel const &other);
	Channel &operator=(Channel const &other);
	~Channel();

    const std::string& getChannelName() const;
    void setChannelName(const std::string& name);

    const std::string& getPassword() const;
    void setPassword(const std::string& password);

    const std::string& getTopic() const;
    void setTopic(const std::string& topic);

    Client* getLeader() const;
    void setLeader(Client* leader);

    const std::string& getMode() const;
    void setMode(const std::string& mode);

    const std::vector<Client*>& getParticipants() const;
}
#endif
