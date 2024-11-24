#include "IrcParser.hpp"

int	main(void)
{
	IrcParser test;
	std::string	input = "  MODE +tikoll username 123 123123 123 "; // put the case;
	tParams	res;
	
	res = test.IrcParsing(3, input);
	test.ShowParams();
	
	return (0);
}