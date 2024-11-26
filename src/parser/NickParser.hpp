#ifndef NICKPARSER_HPP
# define NICKPARSER_HPP

#include "SuperParser.hpp"

class	SuperParser;

class NickParser : public SuperParser
{
	private:
		NickParser( NickParser const &copy );
		NickParser	&operator=( NickParser const &copy );
	protected:
	public:
		NickParser( void );
		~NickParser( void );
		int	CmdParser( void );
};

#endif