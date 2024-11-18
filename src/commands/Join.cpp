// #ifndef JOIN_HPP
// # define JOIN_HPP

#include "Command.hpp"

class Join : public Command {

	public :
		Join();
		~Join();
		int executeCommand(std::vector<std::string> &messages);

	private :
		Join(const Join &other);
		Join* operator=(const Join &other);

		

};


// #endif

Join::Join() {
	_type = "JOIN";
}

Join::~Join() {}

int Join::executeCommand(std::vector<std::string> &messages) {
	// ChannelManager CnManager;

	std::string channelName = messages[1].substr(1); // # 떼고 채널 이름만 가져옴
	// CnManager.joinChannel(channelName); // 채널에 유저 추가

}
