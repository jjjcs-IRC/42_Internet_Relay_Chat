#ifndef COMMANDFACTORY_HPP
# define COMMANDFACTORY_HPP

#include <map>
#include <memory>
#include <string>

#include "Command.hpp"
#include "Join.hpp"
#include "Pass.hpp"
#include "User.hpp"
#include "Nick.hpp"


class CommandFactory {
	private : 
		static CommandFactory* _instance;
		std::map<std::string, Command*> _commandMap;
		// 싱글톤 패턴을 위한 private 생성자
		CommandFactory();
		CommandFactory(CommandFactory const &other);
		CommandFactory &operator=(CommandFactory const &other);

	public :
		~CommandFactory();
		static CommandFactory* getInstance();
		Command* createCommand(const std::string& commandType);
};

#endif

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
