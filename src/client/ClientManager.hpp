/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:27:54 by jimchoi           #+#    #+#             */
/*   Updated: 2024/11/18 13:43:15 by jeakim           ###   ########.fr       */
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
	std::list<Client> get_clientList() const;
	//
	void add_client(int fd);
    void pass_client(int fd);
    bool set_nick_client(int fd, std::string nickname);
    void set_real_client(int fd, std::string realname);
    //
	void delete_client(int fd);
	void delete_client(std::string nickname);
	void delete_clients();
	//
	Client* find_client(int fd);
	Client* find_client_byNick(std::string nickname);
    // std::string print_client(int fd); //
};

#endif