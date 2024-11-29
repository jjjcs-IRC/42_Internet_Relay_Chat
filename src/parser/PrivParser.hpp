#ifndef PRIVPARSER_HPP
# define PRIVPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

class PrivParser : public SuperParser
{
	private:
		PrivParser( PrivParser const &copy );
		PrivParser	&operator=( PrivParser const &copy );
	protected:
	public:
		PrivParser( void );
		~PrivParser( void );
		int	CmdParser( void );
};

#endif