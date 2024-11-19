#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <vector>

class Client{
protected:
	int client_fd;
	std::string userName;
	std::string nickName;
	std::string realName;
	std::vector<std::string> channels;
    bool  passed;
	std::string read_buf;
	std::string write_buf;
public:
	Client();
	Client(int fd);
	Client(int fd, std::string nickname, std::string realname, bool passed);
	Client(const Client &obj);
	Client& operator=(const Client &obj);
	virtual ~Client();
	//
	int get_clientFd() const;
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
	bool check_pass_client() const;
	bool check_join_channel() const;
	void kick_client_from_channel(std::string channel);
	//
	bool operator==(const Client& obj) const
	{
		return client_fd == obj.client_fd;
	}
};

#endif