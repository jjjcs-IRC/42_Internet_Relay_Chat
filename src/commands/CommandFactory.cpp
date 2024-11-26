#include "CommandFactory.hpp"
#include "Join.hpp"
#include "Pass.hpp"
#include "User.hpp"
#include "Nick.hpp"
#include "Mode.hpp"
#include "./privmsg/Privmsg.hpp"
#include "./Invite/Invite.hpp"
#include "./Kick/Kick.hpp"
#include "./Topic/Topic.hpp"

CommandFactory::CommandFactory() {
    // 각 커맨드 인스턴스를 미리 생성하여 맵에 저장
    _commandMap[PASS] = new Pass();
    _commandMap[USER] = new User();
    _commandMap[NICK] = new Nick();
    _commandMap[JOIN] = new Join();
    _commandMap[PRIVMSG] = new Privmsg();
    _commandMap[INVITE] = new Invite();
    _commandMap[KICK] = new Kick();
    _commandMap[TOPIC] = new Topic();
    _commandMap[MODE] = new Mode();

    std::cout << "CommandFactory 생성자" << std::endl;
    // 다른 커맨드들도 여기에 추가
}

CommandFactory* CommandFactory::getInstance() {
    if (_instance == nullptr) {
        _instance = new CommandFactory();
    }
    return _instance;
}

Command* CommandFactory::createCommand(int commandType) {
    std::map<int, Command*>::iterator it = _commandMap.find(commandType);
    if (it != _commandMap.end()) {
        return it->second;
    }
    return nullptr; // 알 수 없는 커맨드인 경우
}

CommandFactory::~CommandFactory() {
    // 맵에 저장된 모든 커맨드 객체들을 삭제
    std::map<int, Command*>::iterator it;
for (it = _commandMap.begin(); it != _commandMap.end(); ++it) {
    delete it->second;
}
    _commandMap.clear();
}


// 전역 변수 초기화
CommandFactory* CommandFactory::_instance = nullptr;

