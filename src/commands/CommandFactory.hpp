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