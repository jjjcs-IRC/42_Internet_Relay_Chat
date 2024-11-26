// #ifndef COMMANDFACTORY_HPP
// # define COMMANDFACTORY_HPP

// #include <map>
// #include <memory>
// #include <string>

// #include "Command.hpp"
// #include "Join.hpp"
// #include "Pass.hpp"
// #include "User.hpp"
// #include "Nick.hpp"

// class Command;
// class CommandFactory {
// 	private : 
// 		static CommandFactory* _instance;
// 		std::map<int, Command*> _commandMap;
// 		// 싱글톤 패턴을 위한 private 생성자
// 		CommandFactory();
// 		CommandFactory(CommandFactory const &other);
// 		CommandFactory &operator=(CommandFactory const &other);

// 	public :
// 		~CommandFactory();
// 		static CommandFactory* getInstance();
// 		Command* createCommand( int commandType);
// };

// #endif
#ifndef COMMANDFACTORY_HPP
# define COMMANDFACTORY_HPP

#include <map>
#include <memory>
#include <string>
#include "../parser/IrcType.hpp"
#include "Command.hpp"

// 이후에 include
// #include "Join.hpp"
// #include "Pass.hpp"
// #include "User.hpp"
// #include "Nick.hpp"

class CommandFactory {
    private: 
        static CommandFactory* _instance;
        std::map<int, Command*> _commandMap;
        CommandFactory();
        CommandFactory(CommandFactory const &other);
        CommandFactory &operator=(CommandFactory const &other);

    public:
        ~CommandFactory();
        static CommandFactory* getInstance();
        Command* createCommand(int commandType);
};

#endif