#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include "Client.hpp"
#include <list>

class ClientManager
{
private:
	std::list<Client> client_list;
	const std::string server_passwd;
	ClientManager& operator=(const ClientManager&obj);
public:
	ClientManager();
	ClientManager(const ClientManager&obj);
	ClientManager(std::string server_passwd);
	virtual ~ClientManager();
	//
	std::list<Client> get_clientList() const;
	std::string get_server_passwd()const;
	//
	void add_client(int fd, std::string ip);
    void pass_client(int fd);
	void set_user_client(int fd, std::string username);
    bool set_nick_client(int fd, std::string nickname);
    void set_real_client(int fd, std::string realname);
	void set_readBuf(int fd, std::string buf);
	void set_writeBuf(int fd, std::string buf);
    //
	void delete_client(int fd); //fd값으로 client 삭제
	void delete_client_byNick(std::string nickname); //nickName으로 client 삭제
	void delete_clients(); //모든 client 삭제
	//
	bool delete_channel(int fd, std::string ch_name); //user를 channel에서 삭제
	//
	Client* find_client(int fd); //fd값으로 client 찾기
	Client* find_client_byNick(std::string nickname); //nickName으로 client 찾기
	//
	bool check_pass_client(int fd); //해당 fd값의 client의 모든 필드가 저장되었는지 확인
	bool check_name_client(std::string name) const; //userName, nickName 유효성 확인
	//
	std::string get_readBuf(int fd); //fd값으로 client의 readBuf 가져오기
	std::string get_writeBuf(int fd); //fd값으로 client의 writeBuf 가져오기
};

#endif