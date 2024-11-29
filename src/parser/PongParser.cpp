#include "PongParser.hpp"

PongParser::PongParser( void )
{

}

PongParser::~PongParser( void )
{

}

int	PongParser::CmdParser( void )
{
	if (tokens.size() < 2) // The variable must be number 5
		throw (461);
	return (0);
}