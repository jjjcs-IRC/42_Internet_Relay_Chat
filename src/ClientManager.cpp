/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choolee <choolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:33:15 by jimchoi           #+#    #+#             */
/*   Updated: 2024/11/14 19:44:58 by choolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientManager.hpp"

ClientManager::ClientManager()
{
	//
	// std::cout << "Create ClientManager" << std::endl;
}

ClientManager::ClientManager(const ClientManager &obj)
{
	(void)obj;
	// std::cout << "Create and Copy ClientManager" << std::endl;
}

ClientManager& ClientManager::operator=(const ClientManager &obj)
{
	(void)obj;
	// std::cout << "Create and Copy ClientManager" << std::endl;
	return (*this);
}

ClientManager::~ClientManager()
{
	// std::cout << "Delete ClientManager..." << std::endl;
}

void	ClientManager::add_client(int fd) // 추가하는 함수 만듦
{
	Client tmp_client(fd);
	client_list.push_back(tmp_client);
}

void	ClientManager::pass_client(int fd)
{
	Client *tem_client;

	tem_client = find_client(fd);
	tem_client->set_pass();
}

void ClientManager::set_nick_client(int fd, std::string nick_name)
{
	Client *tem_client;

	tem_client = find_client(fd);
	tem_client->set_nickName(nick_name);
}
void ClientManager::set_real_client(int fd, std::string real_name)
{
	Client *tem_client;

	tem_client = find_client(fd);
	tem_client->set_realName(real_name);
}

std::string ClientManager::print_client(int fd)
{
	Client *tem_client;

	tem_client = find_client(fd);
	return (tem_client->get_nickName());
}

Client* ClientManager::find_client(int fd)
{
	Client target_client(fd);
	
	std::list<Client>::iterator it = std::find(client_list.begin(), client_list.end(), target_client);
	
	if (it != client_list.end()) {
        return &(*it);
    } else {
        std::cout << "Object not found." << std::endl;
		return (nullptr);
    }
}

Client* ClientManager::find_client(std::string nickname) const
{
	(void)nickname;
	return (nullptr);
}