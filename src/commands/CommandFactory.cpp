#include "CommandFactory.hpp"

CommandFactory::CommandFactory() {
    // 각 커맨드 인스턴스를 미리 생성하여 맵에 저장
    _commandMap["JOIN"] = new Join();
    _commandMap["PASS"] = new Pass();
    _commandMap["USER"] = new User();
    _commandMap["NICK"] = new Nick();
    // 다른 커맨드들도 여기에 추가
}

CommandFactory* CommandFactory::getInstance() {
    if (_instance == nullptr) {
        _instance = new CommandFactory();
    }
    return _instance;
}

Command* CommandFactory::createCommand(const std::string& commandType) {
    auto it = _commandMap.find(commandType);
    if (it != _commandMap.end()) {
        return it->second;
    }
    return nullptr; // 알 수 없는 커맨드인 경우
}

CommandFactory::~CommandFactory() {
    // 맵에 저장된 모든 커맨드 객체들을 삭제
    for (auto& pair : _commandMap) {
        delete pair.second;
    }
    _commandMap.clear();
}


// 전역 변수 초기화
CommandFactory* CommandFactory::_instance = nullptr;

// 사용 예시

//   
//         Command* command = CommandFactory::getInstance()->createCommand(params, cl, cn);
//         if (command != nullptr) {
//             return command->executeCommand(messages);
//         }
//         return -1; // 에러 코드

