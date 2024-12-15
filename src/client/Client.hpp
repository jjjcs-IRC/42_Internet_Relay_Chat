#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <vector>

class Client{
protected:
	int client_fd;
	std::string client_ip;
	std::string userName;
	std::string nickName;
	std::string realName;
	std::vector<std::string> channels;
    bool  passed;
	std::string read_buf;
	std::string write_buf;
public:
	Client();
	Client(int fd, std::string ip);
	Client(int fd, std::string ip, std::string username, std::string nickname, std::string realname, bool passed);
	Client(const Client &obj);
	Client& operator=(const Client &obj);
	virtual ~Client();
	//
	int get_clientFd() const;
	std::string get_clientIp() const;
	std::string get_userName() const;
	std::string get_nickName() const;
	std::string get_realName() const;
	std::vector<std::string> get_channels() const;
    bool get_passed() const;
	std::string get_readBuf() const;
	std::string get_writeBuf() const;
	//
	void set_clientFd(int fd);
	void set_userName(std::string username);
	void set_nickName(std::string nickname);
	void set_realName(std::string realname);
	bool set_channels(std::string channel);
    void set_passed();
	void set_readBuf(std::string buf);
	void set_writeBuf(std::string buf);
	//
	bool check_pass_client() const; //client의 모든 필드가 저장되었는지 확인
	bool check_join_channel() const; //client가 추가로 채널에 가입할 수 있는지 확인
	bool kick_client_from_channel(std::string channel); //client를 채널에서 삭제하고 채널에 없었으면 false 반환
	//
	bool operator==(const Client& obj) const
	{
		return client_fd == obj.client_fd;
	}
	void appendToWriteBuf(const std::string& message);
};

#endif