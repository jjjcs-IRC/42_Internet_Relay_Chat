// CommandFactory.hpp
#include <map>
#include <memory>
#include <string>



/**
 * CommandFactory 클래스:

싱글톤 패턴을 사용하여 하나의 인스턴스만 존재하도록 함
모든 가능한 커맨드 객체들을 미리 생성하여 맵에 저장
커맨드 타입에 따라 적절한 Command 객체를 반환

사용 예시
    CommandExecutor executor;
    std::vector<std::string> messages = {"param1", "param2"};
    
    // JOIN 커맨드 실행
    int result = executor.executeCommand("JOIN", messages);

	이 방식의 장점:

새로운 커맨드를 추가할 때 기존 코드를 수정할 필요 없음
커맨드 객체들을 재사용할 수 있어 메모리 효율적
타입에 따른 커맨드 실행이 깔끔하게 캡슐화됨

새로운 커맨드를 추가하려면:

새로운 커맨드 클래스를 Command 클래스로부터 상속받아 구현
CommandFactory의 생성자에 새로운 커맨드 추가
*/
class CommandFactory {
private:
    static CommandFactory* _instance;
    std::map<std::string, Command*> _commandMap;
    
    // 싱글톤 패턴을 위한 private 생성자
    CommandFactory() {
        // 각 커맨드 인스턴스를 미리 생성하여 맵에 저장
        _commandMap["JOIN"] = new Join();
        _commandMap["PASS"] = new Pass();
        // 다른 커맨드들도 여기에 추가
    }

public:
    static CommandFactory* getInstance() {
        if (_instance == nullptr) {
            _instance = new CommandFactory();
        }
        return _instance;
    }

    Command* createCommand(const std::string& commandType) {
        auto it = _commandMap.find(commandType);
        if (it != _commandMap.end()) {
            return it->second;
        }
        return nullptr; // 알 수 없는 커맨드인 경우
    }

    ~CommandFactory() {
        // 맵에 저장된 모든 커맨드 객체들을 삭제
        for (auto& pair : _commandMap) {
            delete pair.second;
        }
        _commandMap.clear();
    }
};

// 전역 변수 초기화
CommandFactory* CommandFactory::_instance = nullptr;

// 사용 예시
class CommandExecutor {
public:
    int executeCommand(const std::string& commandType, std::vector<std::string>& messages) {
        Command* command = CommandFactory::getInstance()->createCommand(commandType);
        if (command != nullptr) {
            return command->executeCommand(messages);
        }
        return -1; // 에러 코드
    }
};