/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choolee <choolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:27:54 by jimchoi           #+#    #+#             */
/*   Updated: 2024/11/14 19:45:10 by choolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include "Client.hpp"
#include "list"

class ClientManager
{
private:
	std::list<Client> client_list;
public:
	ClientManager();
	ClientManager(const ClientManager&obj);
	ClientManager& operator=(const ClientManager&obj);
	virtual ~ClientManager();
	//
	Client* get_clientList() const;
	//
	void add_client(int fd); // fd값을 넣어주면 클라이언트 생성 함수
	void pass_client(int fd); // fd값을 넣어주면 해당 fd의 클라이언트의 pass값을 true로 한다.
	void set_nick_client(int fd, std::string nick_name); // fd값과 닉을 넣으면 클라의 닉을 세팅한다.
	void set_real_client(int fd, std::string real_name); // fd값과 리얼네임을 넣으면 클라의 해당 값을 세팅한다.
	std::string print_client(int fd);
	
	void delete_client(int fd);
	void delete_client(std::string nickname);
	//
	Client* find_client(int fd);
	Client* find_client(std::string nickname) const;
};

#endif