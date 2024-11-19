#include "Parse.hpp"

Parse::Parse(void) {};
Parse::~Parse(void) {};

std::vector<std::string> Parse::makeTokens(std::string &read_buf)
{
	std::vector<std::string> raw_tokens;

	if (isEmptyOfAlnum(read_buf)) // "공백들어왔을때 방어", 임시 함수, 공백이 들어왔을때 세그가 뜨는데 원인을 모르겠음.
		return (raw_tokens);
	// std::cout << "here" << std::endl;
	raw_tokens = parseByBNF(read_buf); //그냥 엔터가 들어왔을떄 세그뜸
	return (parseCommandDetails(raw_tokens));
}

std::vector<std::string> Parse::parseByBNF(std::string &read_buf)
{
	std::vector<std::string> params;
	int end_index;

	params = split(read_buf, ' ');
	end_index = params.size() - 1;
	params[end_index].erase(std::remove(params[end_index].begin(), params[end_index].end(), '\n'), params[end_index].end());
	return (params);
}

std::vector<std::string> Parse::parseCommandDetails(std::vector<std::string> &tokens)
{
	switch (identifyCommand(tokens))
	{
	case 0:
		return (parsePASS(tokens));
	case 1:
		return (parseNICK(tokens));
	case 2:
		return (parseUSER(tokens));
	}
	return (tokens); //오류 났을때의 토큰 형태를 정해야 할듯
}

int Parse::identifyCommand(std::vector<std::string> &tokens)
{
	std::string	command_array[3] = {"PASS", "NICK", "USER"};

	if (tokens.size() < 1)
		return (-1);

	for (unsigned long i = 0; i < command_array->length(); i++)
	{
		if (tokens[0] == command_array[i])
		{
			// std::cout << "token : " << tokens[0] << " | command_array : " << command_array[i] << " | i : " << i << std::endl; 
			return (i);
		}
	}
	return (-1);
}

std::string Parse::extractPassword(std::vector<std::string> &tokens)
{
	if (tokens.size() == 0) // 여기서도 터진듯
		return ("");
	if (tokens[0] == "PASS" && tokens.size() == 2)
		return (tokens[1]);
	return ("");
}

std::vector<std::string> Parse::parsePASS(std::vector<std::string> &tokens)
{
	return (tokens);
}

std::vector<std::string> Parse::parseNICK(std::vector<std::string> &tokens)
{
	return (tokens);
}

std::vector<std::string> Parse::parseUSER(std::vector<std::string> &tokens)
{
	return (tokens);
}

// 임시 함수

bool Parse::isEmptyOfAlnum(const std::string& str) {
	if (str.empty()) {
        return true; // 문자열이 비어 있으면 true
    }
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
		// std::cout << static_cast<int>(*it) << std::endl;
        if (std::isalnum(static_cast<unsigned char>(*it))) {
		// std::cout << "here" << std::endl;
            return false; // 숫자나 문자가 있는 경우 false
        }
    }
    return true; // 숫자나 문자가 없는 경우 true
}

std::vector<std::string> Parse::split(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
		if (!token.empty() && !std::all_of(token.begin(), token.end(), isspace)) {
            tokens.push_back(token);
        }
    }
    return tokens;
}