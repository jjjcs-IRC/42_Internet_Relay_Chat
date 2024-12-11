#ifndef IRCBOTPARSER_HPP
# define IRCBOTPARSER_HPP

# include <iostream>
# include <string>
# include <vector>
# include <sstream>
# include <cctype>
# include <exception>

/* Child Class Header */
# include "ParentParser.hpp"
# include "PingParser.hpp"
# include "PrivParser.hpp"
# include <vector>


# define ERROR -1
# define TH_NUM 2

# define PING 0
# define PRIVMSG 1

class IrcBotParser
{
	protected:
		/* parameter manager */
		ParentParser	*ptr;
	private :
		/* Do not use this constructer and operator: Only for OCCF */
		IrcBotParser( IrcBotParser const &copy );
		IrcBotParser 	&operator=( IrcBotParser const &copy );

		/* private functions */
		bool		IsValidString( std::string &CmdLine );
		std::vector<std::string> split(const std::string& str, char delimiter);
		int			GetCmdType( std::vector<std::string> &vec );
		ParentParser	*NewClassPtr( int type );
	public :
		/* OCCF */
		IrcBotParser( void );
		~IrcBotParser( void );

		/* public function */
		std::vector<std::string>	IrcParsing(std::string &CmdLine, std::vector<std::string> &data);
		void						ShowStatus( std::vector<std::string> &data );
};

#endif