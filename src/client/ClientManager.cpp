#include "ClientManager.hpp"

ClientManager::ClientManager()
{
	// std::cout << "Create ClientManager" << std::endl;
}

ClientManager::ClientManager(std::string server_passwd) : server_passwd(server_passwd)
{
	// std::cout << "Create ClientManager" << std::endl;
}

ClientManager::ClientManager(const ClientManager &obj)
{
	std::list<Client>::iterator it;

    for (it = obj.get_clientList().begin(); it != obj.get_clientList().end(); it++)
    {
        Client tmp_client((*it).get_clientFd(), (*it).get_clientIp(), (*it).get_userName(), (*it).get_nickName(), (*it).get_realName(), (*it).get_passed());
	    this->client_list.push_back(tmp_client);
    }
	// std::cout << "Create and Copy ClientManager" << std::endl;
}

ClientManager& ClientManager::operator=(const ClientManager &obj)
{
    std::list<Client>::iterator it;

    for (it = obj.get_clientList().begin(); it != obj.get_clientList().end(); it++)
    {
        Client tmp_client((*it).get_clientFd(), (*it).get_clientIp(), (*it).get_nickName(), (*it).get_userName(), (*it).get_realName(), (*it).get_passed());
	    this->client_list.push_back(tmp_client);
    }
	// std::cout << "Create and Copy ClientManager" << std::endl;
	return (*this);
}

ClientManager::~ClientManager()
{
	// std::cout << "Delete ClientManager..." << std::endl;
}

//

std::list<Client> ClientManager::get_clientList() const
{
    return (this->client_list);
}

std::string ClientManager::get_server_passwd() const
{
    return (this->server_passwd);
}

//

void ClientManager::add_client(int fd, std::string ip)
{
    Client tmp_client(fd, ip);

    this->client_list.push_back(tmp_client);
}

void ClientManager::pass_client(int fd)
{
    Client *tmp_client;

    tmp_client = find_client(fd);
    tmp_client->set_passed();
}

void ClientManager::set_user_client(int fd, std::string username)
{
    Client *tmp_client;

    tmp_client = find_client(fd);
    tmp_client->set_userName(username);
}

bool ClientManager::set_nick_client(int fd, std::string nickname)
{
    Client *tmp_client;

    if (find_client_byNick(nickname) != NULL)
        return (false);
    if (nickname[0] == '#' || nickname[0] == '&')
        return (false);
    tmp_client = find_client(fd);
    tmp_client->set_nickName(nickname);
    return (true);
}

void ClientManager::set_real_client(int fd, std::string realname)
{
    Client *tmp_client;

    tmp_client = find_client(fd);
    tmp_client->set_realName(realname);
}

void ClientManager::set_readBuf(int fd, std::string buf)
{
    Client *tmp_client;

    tmp_client = find_client(fd);
    tmp_client->set_readBuf(buf);
}

void ClientManager::set_writeBuf(int fd, std::string buf)
{
    Client *tmp_client;

    tmp_client = find_client(fd);
    tmp_client->set_writeBuf(buf);
}

//

void ClientManager::delete_client(int fd)
{
    Client tmp_client(fd, "");

    std::list<Client>::iterator it = std::find(this->client_list.begin(), this->client_list.end(), tmp_client);
    this->client_list.erase(it);
}

void ClientManager::delete_client_byNick(std::string nickname)
{
    std::list<Client>::iterator it;

    for (it = this->client_list.begin(); it != this->client_list.end(); it++)
        if (nickname.compare(it->get_nickName()))
            this->client_list.erase(it);
}

void ClientManager::delete_clients()
{
    this->client_list.clear();
}

//

bool ClientManager::delete_channel(int fd, std::string ch_name)
{
    Client* tmp_client;
    
    tmp_client = find_client(fd);
    return tmp_client->kick_client_from_channel(ch_name);
}

//

Client* ClientManager::find_client(int fd)
{
    Client tmp_client(fd, "");

    std::list<Client>::iterator it = std::find(this->client_list.begin(), this->client_list.end(), tmp_client);
    if (it != client_list.end())
        return &(*it);
    // std::cout << "Object not found." << std::endl;
    return (NULL);
}

Client* ClientManager::find_client_byNick(std::string nickname)
{
    std::list<Client>::iterator it;

    for (it = this->client_list.begin(); it != this->client_list.end(); it++)
        if (nickname.compare(it->get_nickName()) == false)
            return &(*it);
    return (NULL);
}

//

bool ClientManager::check_pass_client(int fd)
{
    Client *tmp_client;

    tmp_client = find_client(fd);
    return tmp_client->check_pass_client();
}

bool check_special_char(char c)
{
    if (c == '!' || c == '@' || c == '$')
        return true;
    if (c == '%' || c == '^' || c == '&' || c == '*')
        return true;
    return false;
}

bool ClientManager::check_name_client(std::string name) const //userName, nickName 유효성 확인
{
	if (name.length() <= 0)
		return false;
	if (name[0] == '#') //name 첫 글자가 #인지 확인
		return false;
	if (name.length() >= 10) //name 길이 확인
		return false;
    for (int i = 0; i < name.length(); i++) //숫자, 알파벳, 정해진 특수 문자로 이루어졌는지 확인
        if (isalnum(name[i]) != 0 && !check_special_char(name[i]))
            return false;
	if (name.find(" ") != std::string::npos) //name에 공백이 있는지 확인
		return false;
    return true;
}

//

std::string ClientManager::get_readBuf(int fd)
{
    Client *tmp_client;

    tmp_client = find_client(fd);
    return tmp_client->get_readBuf();
}

std::string ClientManager::get_writeBuf(int fd)
{
    Client *tmp_client;

    tmp_client = find_client(fd);
    return tmp_client->get_writeBuf();
}