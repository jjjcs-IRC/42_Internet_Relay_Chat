#ifndef PARSE_HPP
# define PARSE_HPP

#include <string>
#include <vector>
#include <sstream>

#include "ClientManager.hpp"
// #include "Server.hpp"

// isEmptyOfAlnum를 위한 헤더
#include <cctype>

class Parse {
	private :

	public :
		Parse(void);
		~Parse(void);

		std::vector<std::string> makeTokens(std::string &read_buf);
		std::vector<std::string> parseByBNF(std::string &read_buf);
		std::vector<std::string> parseCommandDetails(std::vector<std::string> &tokens);
		std::string extractPassword(std::vector<std::string> &tokens);
		std::vector<std::string> parsePASS(std::vector<std::string> &tokens);
		std::vector<std::string> parseNICK(std::vector<std::string> &tokens);
		std::vector<std::string> parseUSER(std::vector<std::string> &tokens);
		int identifyCommand(std::vector<std::string> &tokens);

		// 임시 함수
		std::vector<std::string> split(const std::string& str, char delimiter);
		bool isEmptyOfAlnum(const std::string& str);
};

#endif