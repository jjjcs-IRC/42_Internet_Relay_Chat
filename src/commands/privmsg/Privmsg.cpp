/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:15:44 by jeakim            #+#    #+#             */
/*   Updated: 2024/11/18 21:04:30 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "privmsg.hpp"

Privmsg::Privmsg()
{
	this->_type = "PRIVMSG";
}

Privmsg::Privmsg(const Privmsg &obj)
{
	// this->_type = obj.getType();
}

Privmsg& Privmsg::operator=(const Privmsg &obj)
{
	// this->_type = obj.getType();
	return (*this);
}

Privmsg::~Privmsg()
{
	//
}

#include <vector>
#include <sstream>
int Privmsg::executeCommand(std::vector<std::string> &msg, ClientManager &cl, ChannelManager &cn)
{
	if (msg[1].length() == 0)
		return (411);
	if (msg[2].length() == 0)
		return (412);

	msg[1].erase(remove(msg[1].begin(), msg[1].end(), ' '), s.end()); //띄어쓰기 제거
	std::istringstream ss(msg[1]);
	std::vector<std::string> v_client;
	std::vector<std::string> v_channel;
	std::string tmp;
	while (getline(ss, tmp, ',')) //','로 구분
	{
		if (tmp[0] == '#')
			v_channel.push_back(tmp.substr(1)); //#을 떼고 채널명만 저장
		else
			v_client.push_back(tmp);
	}

	if (v_client.size() == 1 && v_channel.size() == 0) // 단일 상대에게 보낼 때 
	{
		//개인 존재 검사(401)
		if (cl.find_client_byNick(v_client[0]) == NULL)
			return 401;
		
	}
	else if (v_client.size() == 0 && v_channel.size() == 1) //단일 채널에 보낼 때
	{
		//채널 이름 형식 검사(413)
		// if ()
			return 413;

		//채널 존재 검사(403)
		// if (cn.find_())
			return 403;

		//클라이언트가 채널에 가입되어있는지 검사(404)
		// if (cn.find_client(v_client[0]))
			return 404;
		
	}
	else //다중 대상에게 보낼 때
	{
		// for (int i = 0; i < v_channel.size(); i++) //채널 이름 형식 검사(413)
		// 	if (cn.find_channel(v_channel[i]) == NULL)
		// 		return 407;
		// for (int i = 0; i < v_channel.size(); i++) //채널 존재 검사(403)
		// 	if (cn.find_channel(v_channel[i]) == NULL)
		// 		return 407;
		for (int i = 0; i < v_client.size(); i++) //클라이언트가 
			if (cl.find_client_byNick(v_client[i]) == NULL)
				return 407;
	}
	
}

// #include <vector>
// #include <sstream>
// int Privmsg::executeCommand(std::vector<std::string> &msg, ClientManager &cl, ChannelManager &cn)
// {
// 	msg[1].erase(remove(msg[1].begin(), msg[1].end(), ' '), s.end()); //띄어쓰기 제거
	
// 	std::istringstream ss(msg[1]);
// 	std::vector<std::string> v_client;
// 	std::vector<std::string> v_channel;
// 	std::string tmp;
// 	while (getline(ss, tmp, ',')) //','로 구분
// 	{
// 		if (tmp[0] == '#')
// 			v_channel.push_back(tmp.substr(1)); //#을 떼고 채널명만 저장
// 		else
// 			v_client.push_back(tmp);
// 	}

// 	if (v_client.size() > 0)
// 		//ERR_NOSUCHNICK (401)
// 		//제공된 닉네임에 해당하는 클라이언트를 찾을 수 없음
// 		for (int i = 0; i < v_client.size(); i++)
// 			if (cl.find_client_byNick(v_client[i]) == NULL)
// 				return 401;
// 	if (msg[1])
// 	{
// 		//ERR_NOSUCHSERVER (402)
// 		//제공된 서버 이름이 존재하지 않음
// 	}
// 	if ()
// 	{
// 		//ERR_CANNOTSENDTOCHAN (404)
// 		//PRIVMSG / NOTICE가 <채널>에 전달되지 않았음
// 		//이는 일반적으로 채널 모드로 인해 발생하며, 예를 들어 채널이 '모더레이션' 상태이고 클라이언트가 채널에서 발언할 권한이 없거나, 외부 메시지를 허용하지 않는 모드가 설정된 채널에 참여하지 않은 경우에 응답으로 전송됩니다.
		
// 		//모더레이션 상태인 경우, 클라이언트가 발언한 권한이 있는지 확인

// 		//외부 메세지 불허인 경우, 클라이언트가 채널에 참여했는지 확인
		
// 		return (404);
// 	}
// 	if ()
// 	{
// 		//ERR_TOOMANYTARGETS (407)
// 		//수신 대상이 너무 많은 경우
// 	}
// 	if (v_client.size() == 0 && v_channel.size() == 0)
// 	{
// 		//ERR_NORECIPIENT (411)
// 		//PRIVMSG 명령어에 의해 반환
// 		//수신자가 지정되지 않아 메시지가 전달되지 않았음
// 		return (411);
// 	}
// 	if (msg[2].length() == 0)
// 	{
// 		//ERR_NOTEXTTOSEND (412)
// 		//PRIVMSG 명령어에 의해 반환
// 		//보낼 텍스트가 없어 메시지가 전달되지 않았음
// 		return (412);
// 	}
// 	if ()
// 	{
// 		//ERR_NOTOPLEVEL (413)
// 	}
// 	if ()
// 	{
// 		//ERR_WILDTOPLEVEL (414)
// 		//닉네임 <nick>을 가진 사용자가 현재 자리 비움 상태
// 		//사용자가 설정한 자리 비움 메시지를 전송
// 	}
// }