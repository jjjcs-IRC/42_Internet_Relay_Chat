#ifndef PINGPARSER_HPP
# define PINGPARSER_HPP

#include "ParentParser.hpp"

class ParentParser;

class PingParser : public ParentParser
{
	private:
		PingParser( PingParser const &copy );
		PingParser	&operator=( PingParser const &copy );
	protected:
	public:
		PingParser( void );
		~PingParser( void );
		int	CmdParser( void );
};

#endif