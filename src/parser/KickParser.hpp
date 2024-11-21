#ifndef KICKPARSER_HPP
# define KICKPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

class KickParser : public SuperParser
{
	private:
		KickParser( KickParser const &copy );
		KickParser	&operator=( KickParser const &copy );
	protected:
	public:
		KickParser( void );
		~KickParser( void );
		int	CmdParser( void );
};

#endif