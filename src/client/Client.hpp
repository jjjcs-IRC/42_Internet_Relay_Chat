/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:52:27 by jimchoi           #+#    #+#             */
/*   Updated: 2024/11/15 19:09:46 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <vector>

class Client{
protected:
	int client_fd;
	std::string nickName;
	std::string realName;
	std::vector<std::string> channels;
    bool  passed;
public:
	Client();
	Client(int fd);
	Client(int fd, std::string nickname, std::string realname, bool passed);
	Client(const Client &obj);
	Client& operator=(const Client &obj);
	virtual ~Client();
	//
	int get_clientFd() const;
	std::string get_nickName() const;
	std::string get_realName() const;
	std::vector<std::string> get_channels() const;
    bool get_passed() const;
	//
	void set_clientFd(int fd);
	void set_nickName(std::string nickname);
	void set_realName(std::string realname);
	void set_channels(std::string channel);
    void set_passed();
	//
	bool check_pass_client(int fd) const;
	//
	bool operator==(const Client& obj) const
	{
		return client_fd == obj.client_fd;
	}
};

#endif