#include "IrcParser.hpp"

int	main(void)
{
	IrcParser test;
	std::string	input = ": "; // put the case;
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