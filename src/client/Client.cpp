#include "Client.hpp"

Client::Client() : client_fd(-1), passed(false)
{
	// std::cout << "Create Client!!!" << std::endl;
}

Client::Client(int fd, std::string ip) : client_fd(fd), client_ip(ip), passed(false)
{
	// this->nickName = "*";
	// std::cout << "Create Client!!!" << std::endl;
}

Client::Client(int fd, std::string ip, std::string username, std::string nickname, std::string realname, bool passed) : client_fd(fd), client_ip(ip), userName(username), nickName(nickname), realName(realname), passed(passed)
{
	//std::cout << "Create Client!!!" << std::endl;
}

Client::Client(const Client &obj)
{
	this->client_fd = obj.client_fd;
	this->client_ip = obj.get_clientIp();
	this->userName = obj.get_userName();
	this->nickName = obj.get_nickName();
	this->realName = obj.get_realName();
	// this->channels = obj.get_channels();
	for (unsigned long i = 0; i < obj.get_channels().size(); i++)
		this->channels.push_back(obj.get_channels()[i]);
	// std::cout << "Create and Copy Client!!!" << std::endl;
}

Client& Client::operator=(const Client &obj)
{
	this->client_fd = obj.get_clientFd();
	this->client_ip = obj.get_clientIp();
	this->userName = obj.get_userName();
	this->nickName = obj.get_nickName();
	this->realName = obj.get_realName();
	// this->channels = obj.get_channels();
	for (unsigned long i = 0; i < obj.get_channels().size(); i++)
		this->channels.push_back(obj.get_channels()[i]);
	// std::cout << "Create and Copy Client!!!" << std::endl;
	return (*this);
}

Client::~Client()
{
	// std::cout << "Delete Client..." << std::endl;
}

//

int Client::get_clientFd() const
{
	return (this->client_fd);
}

std::string Client::get_clientIp() const
{
	return (this->client_ip);
}

std::string Client::get_userName() const
{
	return (this->userName);
}

std::string Client::get_nickName() const
{
	return (this->nickName);
}

std::string Client::get_realName() const
{
	return (this->realName);
}

std::vector<std::string> Client::get_channels() const
{
	return (this->channels);
}

bool Client::get_passed() const
{
    return (this->passed);
}

std::string Client::get_readBuf() const
{
	return (this->read_buf);
}

std::string Client::get_writeBuf() const
{
	return (this->write_buf);
}

//

void Client::set_clientFd(int fd)
{
	this->client_fd = fd;
}

void Client::set_userName(std::string username)
{
	this->userName = username;
}

void Client::set_nickName(std::string nickname)
{
	this->nickName = nickname;
}

void Client::set_realName(std::string realname)
{
	this->realName = realname;
}

bool Client::set_channels(std::string channel)
{
	if (this->channels.size() >= 10)
		return false;
	this->channels.push_back(channel);
	return true;
}

void Client::set_passed()
{
    this->passed = true;
}

void Client::set_readBuf(std::string buf)
{
	this->read_buf.clear();
	this->read_buf = buf.substr();
}

void Client::set_writeBuf(std::string buf)
{
	this->write_buf.clear();
	this->write_buf = buf.substr();
}

//

bool Client::check_pass_client() const
{
	if (this->client_fd < 0)
		return (false);
	if (this->userName.empty())
		return (false);
	if (this->nickName.empty())
		return (false);
	if (this->realName.empty())
		return (false);
	if (!this->passed)
		return (false);
	return (true);
}

bool Client::check_join_channel() const
{
	if (this->channels.size() >= 10)
		return false;
	return true;
}

bool Client::kick_client_from_channel(std::string channel)
{
	std::vector<std::string>::iterator it;

	it = find(this->channels.begin(), this->channels.end(), channel);
	if (it == this->channels.end())
		return false;
	else
		this->channels.erase(it);
	return true;
}