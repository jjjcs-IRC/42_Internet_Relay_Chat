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
	{
		std::cerr << "Error: abt parameters" << std::endl;
		throw (411);
	}

	int	pos = tokens[0].find('!');
	std::string	Nick = tokens[0].substr(0, pos);
	std::string	Addr = tokens[0].substr(pos, strlen(tokens[0].c_str()) - pos);

	std::vector<std::string>	res;
	res.push_back(Nick);
	res.push_back(Addr);
	for (int i = 1; i < tokens.size(); i++)
		res.push_back(tokens[i]);
	tokens = res;
	return (0);
}