#include "NickParser.hpp"

NickParser::NickParser( void )
{
	
}

NickParser::~NickParser( void )
{

}

int	NickParser::CmdParser( void )
{
	if (tokens.size() == 1)
		throw (431);
	return (0);
}