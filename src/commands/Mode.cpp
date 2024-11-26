#include "Mode.hpp"
#include "../server/Server.hpp"


Mode::Mode() {}

Mode::~Mode() {}

Mode &Mode::operator=(const Mode &other) {
	(void)other;
	return (*this);
}

Mode::Mode(const Mode &other) {
	(void)other;
}

std::vector<std::string> Mode::modeSplit(std::string str, char Delimiter) {
	std::istringstream iss(str);             // istringstream에 str을 담는다.
	std::string buffer;                      // 구분자를 기준으로 절삭된 문자열이 담겨지는 버퍼

	std::vector<std::string> result;

	// istringstream은 istream을 상속받으므로 getline을 사용할 수 있다.
	while (getline(iss, buffer, Delimiter)) {
		result.push_back(buffer);               // 절삭된 문자열을 vector에 저장
	}

	return result;
}

int Mode::executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn) {
	Client *client = cl.find_client(params.client_fd);
	Channel *channel = cn.findChannel(params.tokens[1]);
	std::cout << "Mode::executeCommand" << std::endl;
	// if (client->get_passed() == false) {
	// 	// `ERR_NOTREGISTERED (451)`
	// 	// `USER` 명령어로 사용자 정보를 등록하기 전에 다른 명령어를 사용하려고 하면 이 에러가 발생합니다.
	// 	// "<client> :You have not registered"
	// 	std::cout << "not passed" << std::endl;
	// 	throw 451;
	// }
	std::cout << "Mode::executeCommand 2..." << std::endl;
	
	std::string result;
	std::vector<std::string> modes;

	for (size_t i = 1; i < params.tokens.size(); i++) {
		std::cout << "params.tokens[" << i << "] : " << params.tokens[i] << std::endl;
		std::vector<std::string> modes = modeSplit(params.tokens[i], ':');
		// for(size_t j = 0; j < modes.size(); j++) {
		// 	std::cout << "modes[" << j << "] : " << modes[j] << std::endl;
		// }
		
		if (modes[1] == "i") {
			result += modeI(modes);
		}
		else if (modes[1] == "o") {

		}
		else if (modes[1] == "l") {

		}
		else if (modes[1] == "k") {

		}
		else if (modes[1] == "t") {

		}
		else {
			// `ERR_UNKNOWNMODE (472)`
			// "<client> :is unknown mode char to me for <channel>"
			throw 472;
		}

	}

}

std::string Mode::modeI (std::vector<std::string> &cmd) {
	std::cout << "Mode::modeI" << std::endl;
	return "modeI";
}

std::string Mode::modeO (std::vector<std::string> &cmd) {
	std::cout << "Mode::modeO" << std::endl;
	return "modeO";
}

std::string Mode::modeL (std::vector<std::string> &cmd) {
	std::cout << "Mode::modeL" << std::endl;
	return "modeL";
}

std::string Mode::modeK (std::vector<std::string> &cmd) {
	std::cout << "Mode::modeK" << std::endl;
	return "modeK";
}

std::string Mode::modeT (std::vector<std::string> &cmd) {
	std::cout << "Mode::modeT" << std::endl;
	return "modeT";
}