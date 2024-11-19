#include "Channel.hpp"

Channel::Channel(const std::string& name, const std::string& password)
    : channelName(name), password(password), leader(NULL) {}


Channel::Channel(const Channel& other): channelName(other.channelName), password(other.password), topic(other.topic), 
      leader(other.leader), channelMode(other.mode), participants(other.participants) {}

Channel& Channel::operator=(const Channel& other) {
    if (this != &other) {
        channelName = other.channelName;
        password = other.password;
        topic = other.topic;
        leader = other.leader;
        channelMode = other.mode;
        participants = other.participants;
    }
    return *this;
}

Channel::~Channel() {}

const std::string& Channel::getChannelName() const {
    return channelName;
}

void Channel::setChannelName(const std::string& name) {
    channelName = name;
}

const std::string& Channel::getPassword() const {
    return password;
}

void Channel::setPassword(const std::string& password) {
    this->password = password;
}

const std::string& Channel::getTopic() const {
    return topic;
}

void Channel::setTopic(const std::string& topic) {
    this->topic = topic;
}

User* Channel::getLeader() const {
    return leader;
}

void Channel::setLeader(Client* leader) {
    this->leader = leader;
}

const std::string& Channel::getMode() const {
    return mode;
}

void Channel::setMode(const std::string& mode) {
    this->mode = mode;
}

const std::vector<User*>& Channel::getParticipants() const {
    return participants;
}

void Channel::addParticipant(Client* participant) {
    this->participants.push_back(participant);
}

// 채널 내 사용자 수 확인
size_t Channel::getParticipantCount() const {
    return participants.size();
}

// TODO: invite 모드이면 invite가 허용된 client만 채널에 입장할 수 있도록 하기