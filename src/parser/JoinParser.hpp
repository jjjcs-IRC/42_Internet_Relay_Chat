#ifndef JOINPARSER_HPP
# define JOINPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

class JoinParser : public SuperParser
{
	private:
		JoinParser( JoinParser const &copy );
		JoinParser	&operator=( JoinParser const &copy );
	protected:
	public:
		JoinParser( void );
		~JoinParser( void );
		int	CmdParser( void );
};

#endif