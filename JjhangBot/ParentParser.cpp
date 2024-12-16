#include "ParentParser.hpp"


ParentParser::ParentParser( void )
{

}

void	ParentParser::SetTokens( std::vector<std::string> &token )
{
	this->tokens = token;
}

std::vector<std::string> ParentParser::GetTokens( void ) const
{
	return (tokens);
}

ParentParser::~ParentParser( void )
{

}
