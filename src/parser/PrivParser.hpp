#ifndef PrivParser_HPP
# define PrivParser_HPP

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