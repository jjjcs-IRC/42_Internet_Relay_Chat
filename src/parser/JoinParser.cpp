#include "JoinParser.hpp"

JoinParser::JoinParser( void )
{
	
}

JoinParser::~JoinParser( void )
{

}

int	JoinParser::CmdParser( void )
{
    for (size_t i = 0; i < tokens.size(); ++i) {
        std::cout << tokens[i];
        if (i < tokens.size() - 1) {
            std::cout << ", ";
        }
    }
	std::cout << std::endl;
	if (tokens.size() < 2)
		throw (461);
	return (0);
}