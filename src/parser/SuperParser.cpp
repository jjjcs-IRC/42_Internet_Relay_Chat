#include "SuperParser.hpp"


SuperParser::SuperParser( void )
{

}

void	SuperParser::SetTokens( std::vector<std::string> token )
{
	this->tokens = token;
}

std::vector<std::string> SuperParser::GetTokens( void ) const
{
	return (tokens);
}

SuperParser::~SuperParser( void )
{

}
