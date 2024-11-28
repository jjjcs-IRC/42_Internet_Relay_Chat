#ifndef MODE_HPP
# define MODE_HPP
#include "../parser/IrcType.hpp"  // tParams 정의를 가져오기 위해
#include "Command.hpp"
#include <sstream>
#include <vector>
#include <algorithm>

#define PLUS 1
#define MINUS 0

class Mode : public Command {

	public :
		Mode();
		~Mode();
		int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn);

	private :
		Mode(const Mode &other);
		Mode& operator=(const Mode &other);
		std::vector<std::string> modeSplit(std::string str, char Delimiter);
		bool removeMode(std::string mode, std::string token);
		bool addMode(std::string mode, std::string token);
		std::string modeI ();
		std::string modeO ();
		std::string modeL ();
		std::string modeK ();
		std::string modeT ();
		bool findOperator(const Client *client);
		bool isNumber(const std::string& str);

		int flag;
		std::string resultOp;
		std::string resultToken;
		std::vector<std::string> modeCmd;
		Channel *channel;
		Client *client;

};



#endif