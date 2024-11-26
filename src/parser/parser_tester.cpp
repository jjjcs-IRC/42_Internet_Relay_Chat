#include "IrcParser.hpp"

int	main(void)
{
	IrcParser test;
	std::string	input = "  MODE +l 1234"; // put the case;
	tParams	res;
	
	try
	{
		/* code */
		res = test.IrcParsing(3, input);
		test.ShowParams();
	}
	catch(int a)
	{
		std::cerr << "error: " << a << '\n';
	}
	
	
	return (0);
}