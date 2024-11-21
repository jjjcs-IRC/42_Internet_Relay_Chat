#ifndef MODEPARSER_HPP
# define MODEPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

class ModeParser : public SuperParser
{
	private:
		ModeParser( ModeParser const &copy );
		ModeParser	&operator=( ModeParser const &copy );
	protected:
	public:
		ModeParser( void );
		~ModeParser( void );
		int	CmdParser( void );
};

#endif