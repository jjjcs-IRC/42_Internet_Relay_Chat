#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector> 
#include "../client/Client.hpp" 
#include <algorithm>
#include <set>

class Channel
{
private:
    std::string channelName;
    std::string password;
    std::string topic;
    std::vector<Client*> operators;
    std::set<char> modes;
    std::vector<Client*> participants;
    std::vector<Client*> invitedClients;
    size_t maxParticipants; // L 모드에서 정한 최대 참여자 수

    bool isInvited(Client* client) const; // 초대 여부 확인
    size_t getParticipantCount() const;  // 채널 내 클라이언트 수 확인

    struct ClientFinder {
        explicit ClientFinder(const std::string& name);
        bool operator()(Client* client) const;
        
        private:
            const std::string& name;
    };

    
    bool isValidePassword(std::string password) const;


public:
    Channel(const std::string& name, Client *user, const std::string& password = "");
	Channel(Channel const &other);
	Channel &operator=(Channel const &other);
	~Channel();

    const std::string& getChannelName() const;
    bool setChannelName(const std::string& name);

    const std::string& getPassword() const;
    bool setPassword(const std::string& password);

    const std::string& getTopic() const;
    bool setTopic(const std::string& topic, Client *client);

    const std::vector<Client*>& getOperators() const;
    bool addOperator(Client* user); //operator 추가

    const std::vector<Client*>& getParticipants() const;
    bool addParticipant(Client* participant); // 클라이언트 채널 입장
   
    bool inviteClient(Client* client); // 클라이언트 초대

    bool isUnderCapacity() const; // 현재 참여 가능 여부 확인 (최대 인원을 넘지 않았는지)
    void setMaxParticipants(size_t max); // L 모드 최대 참여자 설정

    bool removeParticipantByName(const std::string& name); // 클라이언트 채널에서 삭제
    bool isOperator(Client* client) const; // operators 목록에서 클라이언트가 존재하는지 확인
    bool removeOperatorByName(const std::string& name); // 오퍼레이터 채널에서 삭제

    Client* findClient(const std::string& name);// 해당 이름의 클라이언트 찾기
    bool isValideName(std::string channelName) const; // 유효한 이름인지 확인

    // 모드 관련 메서드
    void addMode(char mode);      // 모드 추가
    void removeMode(char mode);  // 모드 제거
    bool hasMode(char mode) const; // 모드 존재 여부 확인
};

#endif