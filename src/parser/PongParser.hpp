#ifndef PONGPARSER_HPP
# define PONGPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

class PongParser : public SuperParser
{
	private:
		PongParser( PongParser const &copy );
		PongParser	&operator=( PongParser const &copy );
	protected:
	public:
		PongParser( void );
		~PongParser( void );
		int	CmdParser( void );
};

#endif