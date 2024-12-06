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
	if (params.tokens.size() == 1) { // 매개변수가 충분하지 않을 때
		// params.tokens.push_back(channel->getMode());
		// std::cout << "모드 확인" << channel->getMode() << params.tokens.size()<< std::endl;

		throw 324;
	}
	// if (params.tokens.size() < 2) { // 매개변수가 충분하지 않을 때
	// 	// throw 461;
	// 	return 0;
	// }
	if (channel->isOperator(client) == false) { // 클라이언트가 오퍼레이터가 아닐 때
		std::cout << "오퍼레이터가 아님" <<params.tokens[1] << std::endl;
		throw 482;
	}
	this->flag = -1;

	memset(&this->resultOp, 0, sizeof(this->resultOp));
	memset(&this->resultToken, 0, sizeof(this->resultToken));
	for (size_t i = 1; i < params.tokens.size(); i++) {
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


	// 성공한 경우 채널의 모든 사용자에게 변경된 옵션 안내
	// :jimchoi1!~1@crs.42seoul.kr MODE #jimchoii +i
	// :<nickname>!<username>@<host> MODE <channel> <mode> <mode params>
	if (resultOp.size() > 0) {
		std::vector<Client*> list =  channel->getParticipants();
		std::string mode_msg = ":" + client->get_nickName() + "!~" + client->get_userName() +\
								"@" + client->get_clientIp() + " MODE " + channel->getChannelName()
								+ " :" + resultOp + " " + resultToken + "\r\n";
		for (int i = 0; i < list.size(); i++)
			list[i]->set_writeBuf(mode_msg);
	}
	return 0;
}

std::string Mode::modeI () {

	// 이미 적용된 옵션인 경우
	if ((channel->hasMode('i') && modeCmd[0] == "+") ||(!channel->hasMode('i') && modeCmd[0] == "-")) {
		return "";
	}

	if (modeCmd[0] == "+") {
		channel->addMode('i');
		if (this->flag == PLUS) {
			return "i";
		}
		else {
			this->flag = PLUS;
			return "+i";
		}
	}
	else {
		channel->removeMode('i');
		if (this->flag == MINUS)
			return "i";
		else {
			this->flag = MINUS;
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
		if (channel->isOperator(client) == true)
			return "";
		channel->addOperator(client);
		if (this->flag == PLUS)
			return "o";
		else {
			this->flag = PLUS;
			return "+o";
		}
	}
	else {
		if (channel->isOperator(client) == false)
			return "";
		channel->removeOperatorByName(client->get_userName());
		if (this->flag == MINUS)
			return "o";
		else {
			this->flag = MINUS;
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
		if (this->flag == PLUS)
			return "l";
		else {
			this->flag = PLUS;
			return "+l";
		}
	}
	else {
		channel->removeMode('l');
		channel->setMaxParticipants(100); // 기본값
		if (this->flag == MINUS)
			return "l";
		else {
			this->flag = MINUS;
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
		if (this->flag == PLUS)
			return "k";
		else {
			this->flag = PLUS;
			return "+k";
		}
	}
	else {
		channel->removeMode('k');
		channel->removePassword();
		if (this->flag == MINUS)
			return "k";
		else {
			this->flag = MINUS;
			return "-k";
		}
	}
}

std::string Mode::modeT () {
	if ((channel->hasMode('t') && modeCmd[0] == "+") || (!channel->hasMode('t') && modeCmd[0] == "-")) {
		return "";
	}
	
	if (modeCmd[0] == "+") {
		channel->addMode('t');
		if (this->flag == PLUS)
			return "t";
		else{
			this->flag = PLUS;
			return "+t";
		}
	}
	else {
		channel->removeMode('t');
		if (this->flag == MINUS)
			return "t";
		else {
			this->flag = MINUS;
			return "-t";
		}
	}
}

// bool Mode::findOperator(const Client *client) {
// 	std::vector<Client*> operators = channel->getOperators();
// 	// if (find(operators.begin(), operators.end(), client) == operators.end())
// 	// 	return false;
// 	for (size_t i = 0; i < operators.size(); i++) {
		
// 		std::cout << "operators[" << i << "] : " << operators[i]->get_userName() << std::endl;
// 	}
// 	return true;
// }

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
