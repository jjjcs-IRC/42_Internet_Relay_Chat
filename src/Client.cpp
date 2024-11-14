/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choolee <choolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:02:19 by jimchoi           #+#    #+#             */
/*   Updated: 2024/11/14 16:49:57 by choolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : client_fd(-1), nickName("NULL"), realName("NULL"), pass(false)
{
	// std::cout << "Create Client!!!" << std::endl;
}

Client::Client(int fd) : client_fd(fd), nickName("NULL"), realName("NULL"), pass(false)
{
	// std::cout << "Create Client!!!" << std::endl;
}

Client::Client(const Client &obj)
{
	this->client_fd = obj.client_fd;
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

//

void Client::set_clientFd(int fd)
{
	this->client_fd = fd;
}

void Client::set_nickName(std::string nickname)
{
	this->nickName = nickname;
}

void Client::set_realName(std::string realname)
{
	this->realName = realname;
}

void Client::set_channels(std::string channel)
{
	this->channels.push_back(channel);
}

void Client::set_pass(void) // ture로 바꿔주는 함수
{
	this->pass = true;
}