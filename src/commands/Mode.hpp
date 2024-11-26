#ifndef MODE_HPP
# define MODE_HPP
#include "../parser/IrcType.hpp"  // tParams 정의를 가져오기 위해
#include "Command.hpp"
#include <sstream>
#include <vector>

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
		std::string modeI (std::vector<std::string> &cmd);
		std::string modeO (std::vector<std::string> &cmd);
		std::string modeL (std::vector<std::string> &cmd);
		std::string modeK (std::vector<std::string> &cmd);
		std::string modeT (std::vector<std::string> &cmd);

		
		

};


#endif