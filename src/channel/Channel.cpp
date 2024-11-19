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

// invite 모드이면 invite가 허용된 client만 채널에 입장 가능
bool Channel::addParticipant(Client* participant) {
    if (mode == "invite") {
        if (!isInvited(participant)) {
            std::cout << participant->getName() << " 채널 입장 안됨." << std::endl; // 확인용 출력 
            return false;
        }
    }
    participants.push_back(participant);
    std::cout << participant->getName() << " 입장 완료" << std::endl;
    return true
}

size_t Channel::getParticipantCount() const {
    return participants.size();
}

bool Channel::inviteClient(Client* client) {
    if (std::find(invitedClients.begin(), invitedClients.end(), client) != invitedClients.end()) {
        std::cout << client->getName() << " 채널에 이미 초대된 사용자" << std::endl;
        return false; // 이미 초대된 경우
    }
    invitedClients.push_back(client);
    std::cout << client->getName() << " 채널 초대 성공" << std::endl;
    return true; // 초대 성공
}

// 초대 여부 확인
bool Channel::isInvited(Client* client) const {
    return std::find(invitedClients.begin(), invitedClients.end(), client) != invitedClients.end();
}
