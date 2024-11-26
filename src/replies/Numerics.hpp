#ifndef NUMERICS_HPP
# define NUMERICS_HPP

#include <string>
#include <iostream>
#include <unistd.h>

#include "../client/ClientManager.hpp"
#include "../channelManager/ChannelManager.hpp"
#include "../parser/IrcType.hpp"

#ifndef SERVER_INFO
#define SERVER_INFO
typedef struct sServerInfo
{
	std::string serverName;
	std::string version;
	std::string userModes;
	std::string channelModes;
	std::string tokens;
	std::string datetime;
} tServerInfo;
#endif

class Numerics {
	private :
		ClientManager &cl;
		ChannelManager &cn;
		tServerInfo &serverInfo;
		tParams params;

	public :
		Numerics(ClientManager &cl, ChannelManager &cn, tServerInfo &serverInfo);
		~Numerics() {};
		void setParams(tParams &params);
		std::string makeUserId(int fd); //":" + nickname + "!" + username + "@localhost" 문구를 만드는 함수
		void dispatchByInt(int fd, int errNum);

		// numeric_replies
		void RPL_WELCOME_001(int fd);
		void RPL_YOURHOST_002(int fd);
		void RPL_CREATED_003(int fd);
		void RPL_MYINFO_004(int fd);
		void RPL_ISUPPORT_005(int fd);
		void ERR_UNKNOWNCOMMAND_421(int fd);

		// INVITE
		void ERR_NEEDMOREPARAMS_461(int fd);
		void ERR_NOSUCHCHANNEL_403(int fd);
		void ERR_NOTONCHANNEL_442(int fd);
		void ERR_USERONCHANNEL_443(int fd);
		void RPL_INVITING_341(int fd);
		void RPL_INVITE(int fd);

		// JOIN
		void RPL_JOIN(int fd);
		void ERR_BANNEDFROMCHAN_474(int fd);
		void ERR_BADCHANNELKEY_475(int fd);

		// KICK
		void ERR_USERNOTINCHANNEL_441(int fd);
		// void ERR_CHANOPRIVSNEEDED_482(int fd);
		void RPL_KICK(int fd);

		// KILL
		void ERR_NOPRIVILEGES_481(int fd);
		void RPL_KILL(int fd);

		// MODE
		/* user mode */
		void MODE_USERMSG(int fd);
		void ERR_UMODEUNKNOWNFLAG_501(int fd);
		void ERR_USERSDONTMATCH_502(int fd);
		void RPL_UMODEIS_221(int fd);

		/* channel mode */
		void MODE_CHANNELMSG(int fd);
		void MODE_CHANNELMSGWITHPARAM(int fd);
		void RPL_CHANNELMODEIS_324(int fd);
		void ERR_CANNOTSENDTOCHAN_404(int fd);
		void ERR_CHANNELISFULL_471(int fd);
		void ERR_CHANOPRIVSNEEDED_482(int fd);
		void ERR_INVALIDMODEPARAM_696(int fd);
		void RPL_ADDVOICE(int fd);

		// MOTD
		void ERR_NOSUCHSERVER_402(int fd);
		void ERR_NOMOTD_422(int fd);
		void RPL_MOTDSTART_375(int fd);
		void RPL_MOTD_372(int fd);
		void RPL_ENDOFMOTD_376(int fd);

		// NAMES
		void RPL_NAMREPLY_353(int fd);
		void RPL_ENDOFNAMES_366(int fd);

		// NICK
		void ERR_NONICKNAMEGIVEN_431(int fd);
		void ERR_ERRONEUSNICKNAME_432(int fd);
		void ERR_NICKNAMEINUSE_433(int fd);
		void RPL_NICK(int fd);

		// NOTICE
		void RPL_NOTICE(int fd);

		// OPER
		void ERR_NOOPERHOST_491(int fd);
		void RPL_YOUREOPER_381(int fd);

		// PART
		void RPL_PART(int fd);

		// PASS
		void ERR_PASSWDMISMATCH_464(int fd);

		// PING
		void RPL_PONG(int fd);

		// QUIT
		void RPL_QUIT(int fd);
		void RPL_ERROR(int fd);

		// PRIVMSG
		void ERR_NOSUCHNICK_401(int fd);
		void ERR_NORECIPIENT_411(int fd);
		void ERR_NOTEXTTOSEND_412(int fd);
		void RPL_PRIVMSG(int fd);

		// TOPIC
		void RPL_TOPIC_332(int fd);
		void RPL_NOTOPIC_331(int fd);

		// USER
		void ERR_ALREADYREGISTERED_462(int fd);
	




		
};

#endif