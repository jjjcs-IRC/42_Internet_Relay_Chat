#ifndef PARTPARSER_HPP
# define PARTPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

class PartParser : public SuperParser
{
	private:
		PartParser( PartParser const &copy );
		PartParser	&operator=( PartParser const &copy );
	protected:
	public:
		PartParser( void );
		~PartParser( void );
		int	CmdParser( void );
};

#endif