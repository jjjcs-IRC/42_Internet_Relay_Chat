/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:33:15 by jimchoi           #+#    #+#             */
/*   Updated: 2024/11/18 13:47:43 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientManager.hpp"

ClientManager::ClientManager()
{
	// std::cout << "Create ClientManager" << std::endl;
}

ClientManager::ClientManager(const ClientManager &obj)
{
	std::list<Client>::iterator it;

    for (it = obj.get_clientList().begin(); it != obj.get_clientList().end(); it++)
    {
        Client tmp_client((*it).get_clientFd(), (*it).get_nickName(), (*it).get_realName(), (*it).get_passed());
	    this->client_list.push_back(tmp_client);
    }
	// std::cout << "Create and Copy ClientManager" << std::endl;
}

ClientManager& ClientManager::operator=(const ClientManager &obj)
{
    std::list<Client>::iterator it;

    for (it = obj.get_clientList().begin(); it != obj.get_clientList().end(); it++)
    {
        Client tmp_client((*it).get_clientFd(), (*it).get_nickName(), (*it).get_realName(), (*it).get_passed());
	    this->client_list.push_back(tmp_client);
    }
	// std::cout << "Create and Copy ClientManager" << std::endl;
	return (*this);
}

ClientManager::~ClientManager()
{
	// std::cout << "Delete ClientManager..." << std::endl;
}

std::list<Client> ClientManager::get_clientList() const
{
    return (this->client_list);
}

void ClientManager::add_client(int fd)
{
    Client tmp_client(fd);

    this->client_list.push_back(tmp_client);
}

void ClientManager::pass_client(int fd)
{
    Client *tmp_client;

    tmp_client = find_client(fd);
    tmp_client->set_passed();
}

bool ClientManager::set_nick_client(int fd, std::string nickname)
{
    Client *tmp_client;

    if (find_client_byNick(nickname) != NULL)
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

void ClientManager::delete_client(int fd)
{
    Client tmp_client(fd);

    std::list<Client>::iterator it = std::find(this->client_list.begin(), this->client_list.end(), tmp_client);
    this->client_list.erase(it);
}

void ClientManager::delete_client(std::string nickname)
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

Client* ClientManager::find_client(int fd)
{
    Client tmp_client(fd);

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

// std::string ClientManager::print_client(int fd)
// {
//     Client tmp_client(fd);

//     std::list<Client>::iterator it = std::find(this->client_list.begin(), this->client_list.end(), tmp_client);
//     return ((&(*it))->get_nickName());
// }