#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector> 
#include "../client/Client.hpp" 
#include <algorithm>

class Channel
{
private:
    std::string channelName;
    std::string password;
    std::string topic;
    Client* leader;
    std::string mode;
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

    std::vector<Client*>::iterator findClient(const std::string& name);// 해당 이름의 클라이언트 찾기
    bool isValidateName(std::string channelName) const;



public:
    Channel(const std::string& name, const std::string& password = "");
	Channel(Channel const &other);
	Channel &operator=(Channel const &other);
	~Channel();

    const std::string& getChannelName() const;
    bool setChannelName(const std::string& name);

    const std::string& getPassword() const;
    void setPassword(const std::string& password);

    const std::string& getTopic() const;
    void setTopic(const std::string& topic);

    Client* getLeader() const;
    void setLeader(Client* leader);

    const std::string& getMode() const;
    void setMode(const std::string& mode);

    const std::vector<Client*>& getParticipants() const;
    bool addParticipant(Client* participant); // 클라이언트 채널 입장
   
    bool inviteClient(Client* client); // 클라이언트 초대

    bool isUnderCapacity() const; // 현재 참여 가능 여부 확인 (최대 인원을 넘지 않았는지)
    void setMaxParticipants(size_t max); // L 모드 최대 참여자 설정

    bool removeParticipantByName(const std::string& name); // 클라이언트 채널에서 삭제
};

#endif