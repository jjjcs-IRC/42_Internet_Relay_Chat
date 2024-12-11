#ifndef PRIVPARSER_HPP
# define PRIVPARSER_HPP

#include "ParentParser.hpp"

class SuperParser;

class PrivParser : public ParentParser
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