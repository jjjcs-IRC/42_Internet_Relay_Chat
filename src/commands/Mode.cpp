#include "Mode.hpp"
#include "../server/Server.hpp"


Mode::Mode():op(true) ,channel(NULL), client(NULL)  {}

Mode::~Mode() {}

Mode &Mode::operator=(const Mode &other) {
	(void)other;
	return (*this);
}

Mode::Mode(const Mode &other) {
	(void)other;
}

int Mode::executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn) {
	this->client = cl.find_client(params.client_fd);
	this->channel = cn.findChannel(params.tokens[0]);
	std::cout << "Mode::executeCommand" << std::endl;
	if (client->get_passed() == false) {
		throw 451;
	}
	if (channel == NULL) { //  채널이 없을 때
		throw 403;
	}
	if (client == NULL) { //  클라이언트가 없을 때
		std::cout << "유효하지 않은 클라이언트" << std::endl;
		throw 0;
	}
	this->op = true;
	if (params.tokens[1][0] == '+')
		this->op = false;
	memset(&this->resultOp, 0, sizeof(this->resultOp));
	memset(&this->resultToken, 0, sizeof(this->resultToken));
	for (size_t i = 1; i < params.tokens.size(); i++) {
		std::cout << "params.tokens[" << i << "] : " << params.tokens[i] << std::endl;
		memset(&this->modeCmd, 0, sizeof(this->modeCmd));
		modeCmd = modeSplit(params.tokens[i], ':');

		std::string result = "";
		if (modeCmd[1] == "i") {
			result += modeI();
		}
		else if (modeCmd[1] == "o") {
			result += modeO();
		}
		else if (modeCmd[1] == "l") {
			result += modeL();
		}
		else if (modeCmd[1] == "k") {
			result += modeK();
		}
		else if (modeCmd[1] == "t") {
			result += modeT();
		}
		if (result.size() > 0) {
			resultOp += result;
			resultToken += modeCmd.size() > 2 ? modeCmd[2] : "";
		}
	}

std::cout << "resultOp : "<< resultOp << std::endl;
std::cout <<"resultToken : " << resultToken << std::endl;

	return 0;
}

std::string Mode::modeI () {
	if (channel->hasMode('i') && modeCmd[0] == "+") {
		return "";
	}
	else if (!channel->hasMode('i') && modeCmd[0] == "-") {
		return "";
	}

	if (modeCmd[0] == "+") {
		channel->addMode('i');
		if (this->op == true) {
			return "i";
		}
		else {
			this->op = false;
			return "+i";
		}
	}
	else {
		channel->removeMode('i');
		if (this->op == false)
			return "i";
		else {
			this->op = false;
			return "-i";
		}
	}
}

std::string Mode::modeO () {
	client = channel->findClient(modeCmd[2]);
	if (client == NULL) { // 클라이언트가 없을 때
			return "";
		}
	if (modeCmd[0] == "+") {
		if (findOperator(client) == true)
			return "";
		channel->addOperator(client);
		if (this->op == true)
			return "o";
		else {
			this->op = true;
			return "+o";
		}
	}
	else {
		if (findOperator(client) == false)
			return "";
		channel->removeOperatorByName(client->get_userName());
		if (this->op == false)
			return "o";
		else {
			this->op = false;
			return "-o";
		}
	}
}

std::string Mode::modeL () {
	if (!channel->hasMode('l') && modeCmd[0] == "-") {
		return "";
	}
	if (isNumber(modeCmd[2]) == false) {
		return "";
	}
	if (modeCmd[0] == "+") {
		channel->addMode('l');
		channel->setMaxParticipants(atoi(modeCmd[2].c_str()));
		if (this->op == true)
			return "l";
		else {
			this->op = true;
			return "+l";
		}
	}
	else {
		channel->removeMode('l');
		channel->setMaxParticipants(100); // 기본값
		if (this->op == false)
			return "l";
		else {
			this->op = false;
			return "-l";
		}
	}
}

std::string Mode::modeK () {
	if (!channel->hasMode('k') && modeCmd[0] == "-") {
		return "";
	}
	if (modeCmd[0] == "+") {
		if (channel->setPassword(modeCmd[2]) == false)
			return "";
		channel->addMode('k');
		if (this->op == true)
			return "k";
		else {
			this->op = true;
			return "+k";
		}
	}
	else {
		channel->removeMode('k');
		channel->removePassword();
		if (this->op == false)
			return "k";
		else {
			this->op = false;
			return "-k";
		}
	}
}

std::string Mode::modeT () {
	if (channel->hasMode('t') && modeCmd[0] == "+") {
		return "";
	}
	else if (!channel->hasMode('t') && modeCmd[0] == "-") {
		return "";
	}

	if (modeCmd[0] == "+") {
		channel->addMode('t');
		if (this->op == true)
			return "t";
		else{
			this->op = true;
			return "+t";
		}
	}
	else {
		channel->removeMode('t');
		if (this->op == false)
			return "t";
		else {
			this->op = false;
			return "-t";
		}
	}
}

bool Mode::findOperator(const Client *client) {
	std::vector<Client*> operators = channel->getOperators();
	if (find(operators.begin(), operators.end(), client) == operators.end())
		return false;
	return true;
}

bool Mode::isNumber(const std::string& str) {
	for (size_t i = 0; i < str.size(); i++) {
		if (std::isdigit(str[i]) == 0) return false;
	}
	return true;
}

std::vector<std::string> Mode::modeSplit(std::string str, char Delimiter) {
	std::istringstream iss(str);             // istringstream에 str을 담는다.
	std::string buffer;                      // 구분자를 기준으로 절삭된 문자열이 담겨지는 버퍼
	std::vector<std::string> result;
	while (getline(iss, buffer, Delimiter)) {
		result.push_back(buffer);               // 절삭된 문자열을 vector에 저장
	}

	return result;
}
