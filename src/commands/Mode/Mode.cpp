#include "Mode.hpp"

// Mode::Mode() {}
Mode::Mode() : flag(0), channel(NULL), client(NULL) {
    resultOp.clear();
    resultToken.clear();
    modeCmd.clear();
}

// Mode::~Mode() {}
Mode::~Mode() {
    resultOp.clear();
    resultToken.clear();
    modeCmd.clear();
    channel = NULL;  // 소유권이 없으므로 delete하지 않음
    client = NULL;   // 소유권이 없으므로 delete하지 않음
}

Mode &Mode::operator=(const Mode &other) {
	(void)other;
	return (*this);
}

Mode::Mode(const Mode &other) {
	(void)other;
}

int Mode::executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn) {
	this->client = cl.find_client(params.client_fd);

	if (client->get_passed() == false) {
		throw 451;
	}

	this->channel = cn.findChannel(params.tokens[1]);
	if (channel == NULL) { //  채널이 없을 때
		if (params.tokens[1][0] != '#') {
			throw 501;	
		}
		throw 403;
	}
	if (params.tokens.size() < 3) { // 매개변수가 충분하지 않을 때
		throw 324;
	}
	if (channel->isOperator(client) == false) {
		throw 482;
	}
	std::vector<std::string> modeTokens = Parser(params.tokens);
	this->flag = -1;

	// memset(&this->resultOp, 0, sizeof(this->resultOp));
	// memset(&this->resultToken, 0, sizeof(this->resultToken));
	resultOp.clear();
	resultToken.clear();
	modeCmd.clear();

	for (size_t i = 2; i < modeTokens.size(); i++) {
		// memset(&this->modeCmd, 0, sizeof(this->modeCmd));
		modeCmd.clear();
		modeCmd = modeSplit(modeTokens[i], ':');
		std::cout << "modeTokens : " << modeTokens[i] << std::endl;
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
			resultToken += " ";
		}
		modeCmd.clear();
	}

	// 성공한 경우 채널의 모든 사용자에게 변경된 옵션 안내
	if (resultOp.size() > 0) {
		sendMsgToCh(channel, client);
	}
	std::cout << "Mode::executeCommand end" << std::endl;
		resultOp.clear();
	resultToken.clear();
	modeCmd.clear();
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
	Client *operatorClient = channel->findClient(modeCmd[2]);
	if (operatorClient == NULL) { // 유효하지 않은 사용자일 때
			return "";
		}
	if (modeCmd[0] == "+") {
		if (channel->isOperator(operatorClient) == true)
			return "";
		channel->addOperator(operatorClient);
		if (this->flag == PLUS)
			return "o";
		else {
			this->flag = PLUS;
			return "+o";
		}
	}
	else {
		if (channel->isOperator(operatorClient) == false)
			return "";
		channel->removeOperatorByName(operatorClient->get_nickName());
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
	if (modeCmd[0] == "+") {
		if (isNumber(modeCmd[2]) == false) {
			return "";
		}
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


bool Mode::isNumber(const std::string& str) {
	if (str.size() == 0) return false;
	for (size_t i = 0; i < str.size(); i++) {
		if (std::isdigit(str[i]) == 0) return false;
	}
	return true;
}


std::vector<std::string> Mode::modeSplit(std::string str, char Delimiter) {
    std::istringstream iss(str);
    std::string buffer;
    std::vector<std::string> result;
    
    while (getline(iss, buffer, Delimiter)) {
        result.push_back(buffer);
    }
    return result; 
}
void Mode::sendMsgToCh(Channel *channel, Client *sender)
{
	(void)sender;
	std::vector<Client*> list =  channel->getParticipants();
	if (client == NULL) {
		std::cout << "client is NULL" << std::endl;
	}
	std::string mode_msg = ":" + client->get_nickName() + "!~" + client->get_userName() +\
							"@" + client->get_clientIp() + " MODE " + channel->getChannelName()
							+ " :" + resultOp + " " + resultToken + "\r\n";
	for (unsigned long i = 0; i < list.size(); i++)
	{
			list[i]->appendToWriteBuf(mode_msg);				
	}
}