#pragma once
#ifndef IRCPARSER_HPP
# define IRCPARSER_HPP

# include <iostream>
# include <string>
# include <vector>
# include <sstream>
# include <cctype>
# include <exception>
# include "IrcType.hpp"

class IrcParser
{
	protected:
		/* parameter manager */
	private :
		/* Do not use this constructer and operator: Only for OCCF */
		IrcParser( IrcParser const &copy );
		IrcParser 	&operator=( IrcParser const &copy );

		/* private functions */
		bool		IsValidString( std::string &CmdLine );
		std::vector<std::string> split(const std::string& str, char delimiter);
		int			GetCmdType( std::string &str );
	public :
		/* OCCF */
		IrcParser( void );
		~IrcParser( void );

		/* For bugfix */
		void		ShowStatus( tParams &res );
		/* public function */
		tParams		IrcParsing( int fd, std::string &CmdLine, tParams &data );
};

#endif