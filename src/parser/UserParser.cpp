#include "UserParser.hpp"

UserParser::UserParser( void )
{

}

UserParser::~UserParser( void )
{

}

int	UserParser::CmdParser( void )
{
	if (tokens.size() < 5) // The variable must be number 5
		throw (461);
	return (0);
}