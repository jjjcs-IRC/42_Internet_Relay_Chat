#ifndef USERPARSER_HPP
# define USERPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

class UserParser : public SuperParser
{
	private:
		UserParser( UserParser const &copy );
		UserParser	&operator=( UserParser const &copy );
	protected:
	public:
		UserParser( void );
		~UserParser( void );
		int	CmdParser( void );
};

#endif