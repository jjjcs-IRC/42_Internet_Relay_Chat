#include "Numerics.hpp"

Numerics::Numerics(ClientManager &cl, ChannelManager &cn, tServerInfo &serverInfo) : cl(cl), cn(cn), serverInfo(serverInfo) {};

Numerics::Numerics(const Numerics &other) : cl(other.cl), cn(other.cn), serverInfo(other.serverInfo) {};

Numerics& Numerics::operator=(const Numerics &other)
{
	if (this != &other)
	{
		this->params = other.params;
	}
	return (*this);
}

void Numerics::setParams(tParams &params)
{
	this->params = params;
}

void Numerics::dispatchByInt(int fd, int errNum)
{
	if (472000 <= errNum && errNum <= 472127)
	{
		ERR_UNKNOWNMODE_472(fd, errNum);
		return ;
	}
	switch (errNum)
	{
	case 1:
		RPL_WELCOME_001(fd);
		// break;
	case 2:
		RPL_YOURHOST_002(fd);
		// break;
	case 3:
		RPL_CREATED_003(fd);
		// break;
	case 4:
		RPL_MYINFO_004(fd);
		// break;
	case 5:
		RPL_ISUPPORT_005(fd);
		break;
	case 421:
		ERR_UNKNOWNCOMMAND_421(fd);
		break;
	case 461:
		ERR_NEEDMOREPARAMS_461(fd);
		break;
	case 403:
		ERR_NOSUCHCHANNEL_403(fd);
		break;
	case 442:
		ERR_NOTONCHANNEL_442(fd);
		break;
	case 443:
		ERR_USERONCHANNEL_443(fd);
		break;
	case 341:
		RPL_INVITING_341(fd);
		break;
	case 474:
		ERR_BANNEDFROMCHAN_474(fd);
		break;
	case 475:
		ERR_BADCHANNELKEY_475(fd);
		break;
	case 441:
		ERR_USERNOTINCHANNEL_441(fd);
		break;
	case 482:
		ERR_CHANOPRIVSNEEDED_482(fd);
		break;
	case 481:
		ERR_NOPRIVILEGES_481(fd);
		break;
	case 501:
		ERR_UMODEUNKNOWNFLAG_501(fd);
		break;
	case 502:
		ERR_USERSDONTMATCH_502(fd);
		break;
	case 221:
		RPL_UMODEIS_221(fd);
		break;
	case 324:
		RPL_CHANNELMODEIS_324(fd);
		break;
	case 404:
		ERR_CANNOTSENDTOCHAN_404(fd);
		break;
	case 471:
		ERR_CHANNELISFULL_471(fd);
		break;
	case 402:
		ERR_NOSUCHSERVER_402(fd);
		break;
	case 696:
		ERR_INVALIDMODEPARAM_696(fd);
		break;
	case 422:
		ERR_NOMOTD_422(fd);
		break;
	case 375:
		RPL_MOTDSTART_375(fd);
		break;
	case 372:
		RPL_MOTD_372(fd);
		break;
	case 376:
		RPL_ENDOFMOTD_376(fd);
		break;
	case 332:
		RPL_TOPIC_332(fd);
		// break;
	case 353:
		RPL_NAMREPLY_353(fd);
		// break;
	case 366:
		RPL_ENDOFNAMES_366(fd);
		break;
	case 431:
		ERR_NONICKNAMEGIVEN_431(fd);
		break;
	case 432:
		ERR_ERRONEUSNICKNAME_432(fd);
		break;
	case 433:
		ERR_NICKNAMEINUSE_433(fd);
		break;
	case 491:
		ERR_NOOPERHOST_491(fd);
		break;
	case 381:
		RPL_YOUREOPER_381(fd);
		break;
	case 464:
		ERR_PASSWDMISMATCH_464(fd);
		break;
	case 401:
		ERR_NOSUCHNICK_401(fd);
		break;
	case 411:
		ERR_NORECIPIENT_411(fd);
		break;
	case 412:
		ERR_NOTEXTTOSEND_412(fd);
		break;
	case 331:
		RPL_NOTOPIC_331(fd);
		break;
	case 462:
		ERR_ALREADYREGISTERED_462(fd);
		break;
	case 451:
		ERR_NOTREGISTERED_451(fd);
		break;
	default:
		// std::cout << fd << " No defined Numeric Reply" << std::endl;
		break;
	}
}

std::string Numerics::makeUserId(int fd)
{
	return (":" + cl.find_client(fd)->get_nickName() + "!" + cl.find_client(fd)->get_userName() + "@localhost");
}

void Numerics::sendMsg(int fd, std::string msg)
{
	cl.set_writeBuf(fd, msg);
	write(fd, cl.get_writeBuf(fd).c_str(), cl.get_writeBuf(fd).length());
	cl.set_writeBuf(fd, "");
}

// numeric_replies
void Numerics::RPL_WELCOME_001(int fd)
{
	sendMsg(fd, ":localhost 001 " + cl.find_client(fd)->get_nickName() + " :Welcome to the Internet Relay Network " + makeUserId(fd) + "\r\n");
}
void Numerics::RPL_YOURHOST_002(int fd)
{
	sendMsg(fd, ":localhost 002 " + cl.find_client(fd)->get_nickName() + " :Your host is " + serverInfo.serverName + " (localhost), running version " + serverInfo.version + "\r\n");
}
void Numerics::RPL_CREATED_003(int fd)
{
	sendMsg(fd, ":localhost 003 " + cl.find_client(fd)->get_nickName() + " :This server was created " + serverInfo.datetime + "\r\n");
}
void Numerics::RPL_MYINFO_004(int fd)
{
	sendMsg(fd, ":localhost 004 " + cl.find_client(fd)->get_nickName() + " " + serverInfo.serverName + " " + serverInfo.version + " " + serverInfo.userModes + " " + serverInfo.channelModes + "k\r\n");
}
void Numerics::RPL_ISUPPORT_005(int fd)
{
	sendMsg(fd, ":localhost 005 " + cl.find_client(fd)->get_nickName() + " " + serverInfo.tokens + " :are supported by this server\r\n");
}
void Numerics::ERR_UNKNOWNCOMMAND_421(int fd)
{
	cl.set_writeBuf(fd, ":localhost 421 " + cl.find_client(fd)->get_nickName() + " " + params.tokens[0] + " :Unknown command\r\n");
}


// INVITE
void Numerics::ERR_NEEDMOREPARAMS_461(int fd)
{
	cl.set_writeBuf(fd, ":localhost 461 " + cl.find_client(fd)->get_nickName() + " " + params.tokens[0] + " :Not enough parameters.\r\n");
}
void Numerics::ERR_NOSUCHCHANNEL_403(int fd)
{
	cl.set_writeBuf(fd, ":localhost 403 " + cl.find_client(fd)->get_nickName() + " #" + params.tokens[2] + " :No such channel\r\n");
}
void Numerics::ERR_NOTONCHANNEL_442(int fd)
{
	cl.set_writeBuf(fd, ":localhost 442 " + cl.find_client(fd)->get_nickName() + " #" + params.tokens[1] + " :The user is not on this channel.\r\n");
}
void Numerics::ERR_USERONCHANNEL_443(int fd)
{
	cl.set_writeBuf(fd, ":localhost 443 " + cl.find_client(fd)->get_nickName() + " " + cl.find_client(fd)->get_nickName() + " #" + params.tokens[2] + " :Is already on channel\r\n");
}
void Numerics::RPL_INVITING_341(int fd)
{
	cl.set_writeBuf(fd, makeUserId(fd) + " 341 " + cl.find_client(fd)->get_nickName() + " " + cl.find_client(fd)->get_nickName() + " #" + params.tokens[2] + "\r\n");
}
void Numerics::RPL_INVITE(int fd)
{
	// cl.set_writeBuf(fd, makeUserId(fd) + " INVITE " + invited + " #" + params.tokens[2] + "\r\n");
}


// JOIN
void Numerics::RPL_JOIN(int fd)
{
	cl.set_writeBuf(fd, makeUserId(fd) + " JOIN :#" + params.tokens[1] + "\r\n");
}
void Numerics::ERR_BANNEDFROMCHAN_474(int fd)
{
	cl.set_writeBuf(fd, "474 " + cl.find_client(fd)->get_nickName() + " #" + params.tokens[1] + " :Cannot join channel (+b)\r\n");
}
void Numerics::ERR_BADCHANNELKEY_475(int fd)
{
	cl.set_writeBuf(fd, "475 " + cl.find_client(fd)->get_nickName() + " #" + params.tokens[1] + " :Cannot join channel (+k)\r\n");
}

// KICK
void Numerics::ERR_USERNOTINCHANNEL_441(int fd)
{
	cl.set_writeBuf(fd, "441 " + cl.find_client(fd)->get_nickName() + " " + cl.find_client(fd)->get_nickName() + " #" + params.tokens[1] + " :They aren't on that channel\r\n");
}
void Numerics::ERR_CHANOPRIVSNEEDED_482(int fd)
{
	cl.set_writeBuf(fd, "482 " + cl.find_client(fd)->get_nickName() + " #" + params.tokens[1] + " :You're not channel operator\r\n");
}
void Numerics::RPL_KICK(int fd)
{
	// cl.set_writeBuf(fd, makeUserId(fd) + " KICK #" + params.tokens[1] + " " + kicked + " " + reason + "\r\n");
}

// KILL
void Numerics::ERR_NOPRIVILEGES_481(int fd)
{
	cl.set_writeBuf(fd, "481 " + cl.find_client(fd)->get_nickName() + " :Permission Denied- You're not an IRC operator\r\n");
}
void Numerics::RPL_KILL(int fd)
{
	// cl.set_writeBuf(fd, makeUserId(fd) + " KILL " + killed + " " + comment + "\r\n");
}

// MODE
/* user mode */
void Numerics::MODE_USERMSG(int fd)
{
	cl.set_writeBuf(fd, ":" + cl.find_client(fd)->get_nickName() + " MODE " + cl.find_client(fd)->get_nickName() + " :" + params.tokens[2] + "\r\n");
}
void Numerics::ERR_UMODEUNKNOWNFLAG_501(int fd)
{
	cl.set_writeBuf(fd, ":localhost 501 " + cl.find_client(fd)->get_nickName() + " :Unknown MODE flag\r\n");
}
void Numerics::ERR_USERSDONTMATCH_502(int fd)
{
	cl.set_writeBuf(fd, "502 " + cl.find_client(fd)->get_nickName() + " :Cant change mode for other users\r\n");
}
void Numerics::RPL_UMODEIS_221(int fd)
{
	cl.set_writeBuf(fd, ":localhost 221 " + cl.find_client(fd)->get_nickName() + " " + params.tokens[2] + "\r\n");
}

/* channel mode */
void Numerics::MODE_CHANNELMSG(int fd)
{
	cl.set_writeBuf(fd, ":localhost MODE #" + params.tokens[1] + " " + params.tokens[2] + "\r\n");
}
void Numerics::MODE_CHANNELMSGWITHPARAM(int fd)
{
	// cl.set_writeBuf(fd, ":localhost MODE #" + params.tokens[1] + " " + params.tokens[2] + " " + param + "\r\n");
}
void Numerics::RPL_CHANNELMODEIS_324(int fd)
{
	cl.set_writeBuf(fd, ":localhost 324 " + cl.find_client(fd)->get_nickName() + " #" + params.tokens[1] + " " + params.tokens[2] + "\r\n");
}
void Numerics::ERR_CANNOTSENDTOCHAN_404(int fd)
{
	cl.set_writeBuf(fd, "404 " + cl.find_client(fd)->get_nickName() + " #" + params.tokens[1] + " :Cannot send to channel\r\n");
}
void Numerics::ERR_CHANNELISFULL_471(int fd)
{
	cl.set_writeBuf(fd, "471 " + cl.find_client(fd)->get_nickName() + " #" + params.tokens[1] + " :Cannot join channel (+l)\r\n");
}
// void Numerics::ERR_CHANOPRIVSNEEDED_482(int fd)
// {
// 	cl.set_writeBuf(fd, ":localhost 482 " + cl.find_client(fd)->get_nickName() + " #" + params.tokens[1] + " :You're not channel operator\r\n");
// }
void Numerics::ERR_INVALIDMODEPARAM_696(int fd)
{
	// cl.set_writeBuf(fd, "696 " + cl.find_client(fd)->get_nickName() + " #" + params.tokens[1] + " " + params.tokens[2] + " " + password + " : password must only contained alphabetic character\r\n");
}
void Numerics::RPL_ADDVOICE(int fd)
{
	// cl.set_writeBuf(fd, ":" + cl.find_client(fd)->get_nickName() + "!" + username + "@localhost MODE #" + params.tokens[1] + " " + params.tokens[2] + " " + param + "\r\n");
}

// MOTD
void Numerics::ERR_NOSUCHSERVER_402(int fd)
{
	cl.set_writeBuf(fd, ":localhost 402 " + cl.find_client(fd)->get_nickName() + " " + serverInfo.serverName + " :No such server\r\n");
}
void Numerics::ERR_NOMOTD_422(int fd)
{
	cl.set_writeBuf(fd, ":localhost 422 " + cl.find_client(fd)->get_nickName() + " :MOTD File is missing\r\n");
}
void Numerics::RPL_MOTDSTART_375(int fd)
{
	cl.set_writeBuf(fd, ":localhost 375 " + cl.find_client(fd)->get_nickName() + " :- " + serverInfo.serverName + " Message of the day - \r\n");
}
void Numerics::RPL_MOTD_372(int fd)
{
	// cl.set_writeBuf(fd, ":localhost 372 " + cl.find_client(fd)->get_nickName() + " :" + motd_line + "\r\n");
}
void Numerics::RPL_ENDOFMOTD_376(int fd)
{
	cl.set_writeBuf(fd, ":localhost 376 " + cl.find_client(fd)->get_nickName() + " :End of /MOTD command.\r\n");
}

// NAMES
void Numerics::RPL_NAMREPLY_353(int fd)
{
	std::vector<Client *> clientList = cn.findChannel(params.tokens[1])->getParticipants();
	std::string nickList;
	for (std::vector<Client *>::iterator it = clientList.begin(); it != clientList.end(); it++)
	{
		nickList.append(" " + (*it)->get_nickName());
	}
	sendMsg(fd, ":localhost 353 " + cl.find_client(fd)->get_nickName() + " = #" + params.tokens[1] + " :" + nickList + "\r\n");
}
void Numerics::RPL_ENDOFNAMES_366(int fd)
{
	sendMsg(fd, ":localhost 366 " + cl.find_client(fd)->get_nickName() + " #" + params.tokens[1] + " :End of /NAMES list.\r\n");
}


// NICK
void Numerics::ERR_NONICKNAMEGIVEN_431(int fd)
{
	cl.set_writeBuf(fd, ":localhost 431 " + cl.find_client(fd)->get_nickName() + " :No nickname given\r\n");
}
void Numerics::ERR_ERRONEUSNICKNAME_432(int fd)
{
	cl.set_writeBuf(fd, ":localhost 432 " + cl.find_client(fd)->get_nickName() + " " + cl.find_client(fd)->get_nickName() + " :Erroneus nickname\r\n");
}
void Numerics::ERR_NICKNAMEINUSE_433(int fd)
{
	cl.set_writeBuf(fd, ":localhost 433 " + cl.find_client(fd)->get_nickName() + " " + cl.find_client(fd)->get_nickName() + " :Nickname is already in use.\r\n");
}
void Numerics::RPL_NICK(int fd)
{
	// cl.set_writeBuf(fd, ":" + oclient + "!" + uclient + "@localhost NICK " +  client + "\r\n");
}

// NOTICE
void Numerics::RPL_NOTICE(int fd)
{
	// cl.set_writeBuf(fd, ":" + cl.find_client(fd)->get_nickName() + "!" + username + "@localhost NOTICE " + target + " " + message + "\r\n");
}

// OPER
void Numerics::ERR_NOOPERHOST_491(int fd)
{
	cl.set_writeBuf(fd, "491 " + cl.find_client(fd)->get_nickName() + " :No O-lines for your host\r\n");
}
void Numerics::RPL_YOUREOPER_381(int fd)
{
	cl.set_writeBuf(fd, "381 " + cl.find_client(fd)->get_nickName() + " :You are now an IRC operator\r\n");
}

// PART
void Numerics::RPL_PART(int fd)
{
	// cl.set_writeBuf(fd, makeUserId(fd) + " PART #" + channel + " " + (reason.empty() ? "." : reason ) + "\r\n");
}

// PASS
void Numerics::ERR_PASSWDMISMATCH_464(int fd)
{
	cl.set_writeBuf(fd, ":localhost 464 " + cl.find_client(fd)->get_nickName() + " :Password incorrect.\r\n");
}

void Numerics::ERR_NOTREGISTERED_451(int fd)
{
	cl.set_writeBuf(fd, ":localhost 451 " + cl.find_client(fd)->get_nickName() + " :You have not registered");
}

// PING
void Numerics::RPL_PONG(int fd)
{
	// cl.set_writeBuf(fd, makeUserId(fd) + " PONG " + token + "\r\n");
}

// QUIT
void Numerics::RPL_QUIT(int fd)
{
	// cl.set_writeBuf(fd, makeUserId(fd) + " QUIT :Quit: " + reason + "\r\n");
}
void Numerics::RPL_ERROR(int fd)
{
	// cl.set_writeBuf(fd, makeUserId(fd) + " ERROR :" + reason + "\r\n");
}

// PRIVMSG
void Numerics::ERR_NOSUCHNICK_401(int fd)
{
	cl.set_writeBuf(fd, "401 " + cl.find_client(fd)->get_nickName() + " " + params.tokens[1] + " :No such nick/channel\r\n");
}
void Numerics::ERR_NORECIPIENT_411(int fd)
{
	cl.set_writeBuf(fd, "411 " + cl.find_client(fd)->get_nickName() + " :No recipient given PRIVMSG\r\n");
}
void Numerics::ERR_NOTEXTTOSEND_412(int fd)
{
	cl.set_writeBuf(fd, "412 " + cl.find_client(fd)->get_nickName() + " :No text to send\r\n");
}
void Numerics::RPL_PRIVMSG(int fd)
{
	// cl.set_writeBuf(fd, ":" + cl.find_client(fd)->get_nickName() + "!" + username + "@localhost PRIVMSG " + target + " " + message + "\r\n");
}

// TOPIC
void Numerics::RPL_TOPIC_332(int fd)
{
	std::string topic = cn.findChannel(params.tokens[1])->getTopic();
	sendMsg(fd, ":localhost 332 " + cl.find_client(fd)->get_nickName() + " #" + params.tokens[1] + " " + topic + "\r\n");
}
void Numerics::RPL_NOTOPIC_331(int fd)
{
	cl.set_writeBuf(fd, ":localhost 331 " + cl.find_client(fd)->get_nickName() + " #" + params.tokens[1] + " :No topic is set\r\n");
}

// USER
void Numerics::ERR_ALREADYREGISTERED_462(int fd)
{
	cl.set_writeBuf(fd, ":localhost 462 " + cl.find_client(fd)->get_nickName() + " :You may not reregister.\r\n");
}

void Numerics::ERR_UNKNOWNMODE_472(int fd, int errNum)
{
	char modechar = errNum % 1000;
	cl.set_writeBuf(fd, ":localhost 472 " + cl.find_client(fd)->get_nickName() + modechar + " :is unknown mode char to me");
}