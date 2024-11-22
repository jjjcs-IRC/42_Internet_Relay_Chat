#include "Channel.hpp"

Channel::Channel(const std::string& name, Client *user, const std::string& password)
    : channelName(name), password(password), operators(1, user), maxParticipants(100) {
    if (!isValideName(name)) {
        throw std::invalid_argument("유효하지 않은 채널 이름: " + name);
    }

    // 비밀번호가 비어 있지 않은 경우에만 유효성 검사
    if (!password.empty() && !isValidePassword(password)) {
        throw std::invalid_argument("유효하지 않은 비밀번호: " + password);
    }
}

Channel::Channel(const Channel& other): channelName(other.channelName), password(other.password), topic(other.topic), 
      operators(other.operators), mode(other.mode), participants(other.participants) {}

Channel& Channel::operator=(const Channel& other) {
    if (this != &other) {
        channelName = other.channelName;
        password = other.password;
        topic = other.topic;
        operators = other.operators;
        mode = other.mode;
        participants = other.participants;
    }
    return *this;
}

Channel::~Channel() {}

const std::string& Channel::getChannelName() const {
    return channelName;
}

bool Channel::setChannelName(const std::string& name) {
    if(isValideName(name)){
        channelName = name;
        return true;
    }
    return false;
}

const std::string& Channel::getPassword() const {
    return password;
}

bool Channel::setPassword(const std::string& password) {
    if(isValidePassword(password)){
        this->password = password;
        return true;
    }
    return false;
}

const std::string& Channel::getTopic() const {
    return topic;
}

void Channel::setTopic(const std::string& topic) {
    this->topic = topic;
}

const std::vector<Client*>& Channel::getOperators() const {
    return operators;
}

// operators 목록에서 클라이언트가 존재하는지 확인
bool Channel::isOperator(Client* client) const {
    return std::find(operators.begin(), operators.end(), client) != operators.end();
}

bool Channel::addOperator(Client* user) {
    // 존재하는 클라이언트인지 확인 -> clientManager에서 해당 client의 존재여부 boolean 값으로 받기

    // 채널에 존재하는 참여자인지 확인
    Client* client = findClient(user->get_nickName());
    if (!client) {
        return false;
    }

    // 중복 확인 후 추가
    if (!isOperator(client)) {
        operators.push_back(client);
    }

    return true;
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

Client* Channel::findClient(const std::string& name) {
    for (std::vector<Client*>::iterator it = participants.begin(); it != participants.end(); ++it) {
        if ((*it)->get_userName() == name) {
            return *it; // 클라이언트를 찾으면 반환
        }
    }
    return NULL; // 찾지 못하면 NULL 반환
}

Channel::ClientFinder::ClientFinder(const std::string& name) : name(name) {}

bool Channel::ClientFinder::operator()(Client* client) const {
    return client->get_userName() == name;
}

// 채널의 참여자 삭제
bool Channel::removeParticipantByName(const std::string& name) {
    Client* client = findClient(name);
    if (client != NULL) {
        participants.erase(std::remove(participants.begin(), participants.end(), client), participants.end());
        delete client;
        std::cout << name << " 채널에서 삭제" << std::endl;
        return true;
    }

    std::cout << name << " 채널에 존재하지 않는 클라이언트" << std::endl;
    return false;
}

bool Channel::isValideName(std::string channelName) const {
    // 이름이 비어있는지 확인
    if (channelName.empty()) {
        return false;
    }

    // 첫 문자가 # 또는 &인지 확인
    if (channelName[0] != '#') {
        return false;
    }

    // 채널 이름의 길이가 200자를 초과하는지 확인
    if (channelName.size() > 200) {
        return false;
    }

    // 채널 이름에 허용되지 않는 문자 (' ', ASCII 7 (^G), ',')가 있는지 확인
    for (std::string::size_type i = 1; i < channelName.size(); ++i) {
        char c = channelName[i];
        if (c == ' ' || c == '\a' || c == ',') {
            return false;
        }
    }
    return true;
}

bool Channel::isValidePassword(std::string password) const {
   // 비밀번호 길이 확인 (1~32자)
    if (password.empty() || password.size() > 32) {
        return false;
    }

    // 비밀번호에 공백 문자가 있는지 확인
    for (std::string::size_type i = 0; i < password.size(); ++i) {
        if (password[i] == ' ') {
            return false; 
        }
    }

    return true;
}