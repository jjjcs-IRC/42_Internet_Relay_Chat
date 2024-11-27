#include "PrivParser.hpp"

PrivParser::PrivParser( void )
{

}

PrivParser::~PrivParser( void )
{

}

int	PrivParser::CmdParser( void )
{
	if (tokens.size() == 1)
		throw (411);
	return (0);
}