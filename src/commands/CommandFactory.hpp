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
