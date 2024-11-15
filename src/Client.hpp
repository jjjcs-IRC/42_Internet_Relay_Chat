/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choolee <choolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:52:27 by jimchoi           #+#    #+#             */
/*   Updated: 2024/11/14 18:47:43 by choolee          ###   ########.fr       */
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

	bool pass; // password를 통과했는지
public:
	Client();
	Client(int fd);
	Client(const Client &obj);
	Client& operator=(const Client &obj);
	virtual ~Client();
	//
	int get_clientFd() const;
	std::string get_nickName() const;
	std::string get_realName() const;
	std::vector<std::string> get_channels() const;
	//
	void set_clientFd(int fd);
	void set_nickName(std::string nickname);
	void set_realName(std::string realname);
	void set_channels(std::string channel); // add_channel() 같은 기능
	void set_pass(void); // pass를 true로 바꿔주는 함수

	 bool operator==(const Client& other) const {
        return client_fd == other.client_fd;
	 }
};

#endif