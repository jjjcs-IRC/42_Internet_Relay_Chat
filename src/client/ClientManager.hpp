#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include "Client.hpp"
#include <list>

class ClientManager
{
private:
	std::list<Client> client_list;
	const std::string server_passwd;
public:
	ClientManager();
	ClientManager(std::string server_passwd);
	ClientManager(const ClientManager&obj);
	ClientManager& operator=(const ClientManager&obj);
	virtual ~ClientManager();
	//
	std::list<Client> get_clientList() const;
	std::string get_server_passwd()const;
	//
	void add_client(int fd);
    void pass_client(int fd);
	void set_user_client(int fd, std::string username);
    bool set_nick_client(int fd, std::string nickname);
    void set_real_client(int fd, std::string realname);
	void set_readBuf(int fd, std::string buf);
	void set_writeBuf(int fd, std::string buf);
    //
	void delete_client(int fd);
	void delete_client_byNick(std::string nickname);
	void delete_clients();
	//
	bool delete_channel(int fd, std::string ch_name);
	//
	Client* find_client(int fd);
	Client* find_client_byNick(std::string nickname);
	//
	bool check_pass_client(int fd) const;
	//
	std::string get_readBuf(int fd);
	std::string get_writeBuf(int fd);
    // std::string print_client(int fd);
};

#endif