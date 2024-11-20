#include "Channel.hpp"

Channel::Channel(const std::string& name, const std::string& password)
    : channelName(name), password(password), leader(NULL), maxParticipants(100) {}


Channel::Channel(const Channel& other): channelName(other.channelName), password(other.password), topic(other.topic), 
      leader(other.leader), mode(other.mode), participants(other.participants) {}

Channel& Channel::operator=(const Channel& other) {
    if (this != &other) {
        channelName = other.channelName;
        password = other.password;
        topic = other.topic;
        leader = other.leader;
        mode = other.mode;
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

Client* Channel::getLeader() const {
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

const std::vector<Client*>& Channel::getParticipants() const {
    return participants;
}

// invite 모드이면 invite가 허용된 client만 채널에 입장 가능
bool Channel::addParticipant(Client* participant) {
    if (mode == "I" && !isInvited(participant)) { 
        std::cout << participant->get_userName() << " 채널 입장 안됨." << std::endl; // 확인용 출력 
        return false;
    }
    participants.push_back(participant);
    std::cout << participant->get_userName() << " 입장 완료" << std::endl;
    return true;
}

size_t Channel::getParticipantCount() const {
    return participants.size();
}

bool Channel::inviteClient(Client* client) {
    if (std::find(invitedClients.begin(), invitedClients.end(), client) != invitedClients.end()) {
        std::cout << client->get_userName() << " 채널에 이미 초대된 사용자" << std::endl;
        return false; // 이미 초대된 경우
    }
    invitedClients.push_back(client);
    std::cout << client->get_userName() << " 채널 초대 성공" << std::endl;
    return true; // 초대 성공
}

// 초대 여부 확인
bool Channel::isInvited(Client* client) const {
    return std::find(invitedClients.begin(), invitedClients.end(), client) != invitedClients.end();
}

// 현재 채널 참여 가능 여부 확인
bool Channel::isUnderCapacity() const {
    size_t currentCount = participants.size();
    return currentCount < maxParticipants;
}

// L 모드 최대 참여자 설정
void Channel::setMaxParticipants(size_t max) {
    maxParticipants = max;
}

std::vector<Client*>::iterator Channel::findClient(const std::string& name) {
    return std::find_if(participants.begin(), participants.end(),
        [&name](Client* client) {
            return client->get_userName() == name;
        });
}


// 채널의 참여자 삭제
bool Channel::removeParticipantByName(const std::string& name) {
     std::vector<Client*>::iterator it = findClient(name);
    if (it != participants.end()) {
        delete *it; // 메모리 해제
        participants.erase(it); // 벡터에서 제거
        std::cout << name << " 채널에서 삭제" << std::endl;
        return true;
    }

    std::cout << name << " 채널에 존재하지 않는 클라이언트" << std::endl;
    return false;
}

//TODO: 채널의 방장 추가, 제거, 상속