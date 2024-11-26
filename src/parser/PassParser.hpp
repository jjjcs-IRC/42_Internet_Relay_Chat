#ifndef PASSPARSER_HPP
# define PASSPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

class PassParser : public SuperParser
{
	private:
		PassParser( PassParser const &copy );
		PassParser	&operator=( PassParser const &copy );
	protected:
	public:
		PassParser( void );
		~PassParser( void );
		int	CmdParser( void );
};

#endif