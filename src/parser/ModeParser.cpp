#include "ModeParser.hpp"

ModeParser::ModeParser( void )
{

}

ModeParser::~ModeParser( void )
{

}

std::string	ModeParser::MakeToken( char flag, char sign, std::string param )
{
	return (std::string(1, flag) + ":" + std::string(1, sign) + ":" + param);
}

int	ModeParser::IsFlag(char	c) const
{
	if ('i' == c)
		return (true);
	if ('t' == c)
		return (true);
	if ('k' == c)
		return (true);
	if ('o' == c)
		return (true);
	if ('l' == c)
		return (true);
	return (false);
}

inline bool	ModeParser::IsSignString( std::string &str ) const
{
	char	c;

	c = str.at(0);
	if (c == '+' || c == '-')
		return (true);
	return (false);
}

int	ModeParser::IsValidFlag( std::string &flag ) const
{
	int	num = 0;

	{
		std::string::iterator	start = flag.begin();
		std::string::iterator	end = flag.end();
		char sign = *start;
		start++;
		for ( ; start != end ; ++start )
		{
			if (*start == 'o')
				num++;
			if (*start == 'l' && sign == '+')
				num++;
			if (*start == 'k' && sign == '+')
				num++;
			if (IsFlag(*start) == false)
				throw (472 * 1000 + static_cast<int>(*start));
		}
	}
	return ( num );
}

bool	ModeParser::IsDigit( std::string str ) const
{
	std::string::iterator	start = str.begin();
	std::string::iterator	end = str.end();

	for ( ; start != end ; ++start )
	{
		if (!std::isdigit(*start))
			return (false);
	}
	return (true);
}

int	ModeParser::CmdParser( void )
{
	if (DEBUG)
	{
		std::cout << "ModeParser On" << std::endl;
		std::cout << "tokens.size: " << tokens.size() << std::endl;
		std::cout << "========TOKENs==========" << std::endl;
		for (int i = 0; i < tokens.size(); i++)
			std::cout <<"[" << i<< "]" << tokens[i] << std::endl;
	}
	if (tokens.size() < 2)
		throw (461);
	/* sorting strings(flag and parameters ) */
	std::vector<std::string>	flag;
	std::vector<std::string>	params;
	{
		std::vector<std::string>::iterator	start = tokens.begin();
		std::vector<std::string>::iterator	end = tokens.end();
		bool cycle = true;
		for (int i = 0; start != end &&  i < 2 ; i++)
		{
			++start;
		}
		int	ParaNum = 0;
		for ( ; start != end; ++start)
		{
			/* flag */
			if ( cycle )
			{
				if (IsSignString(*start))
				{
					ParaNum = IsValidFlag(*start);
					flag.push_back(*start);
					cycle = false;
				}
				else
				{
					// std::cout << *start << ": ERROR: is not sign string" << std::endl;
					// return (ERROR);
					break ;
				}
			}
			/* parameters */
			else
			{
				for (int i = 0; start != end && i < ParaNum; i++)
					params.push_back(*start);
				ParaNum = 0;
				cycle = true;
			}
		}
	}
	if ( DEBUG )
	{
		
		std::cout << "DEBUGER::PARAMS" << std::endl;
		std::cout << "params_size: " << params.size() << std::endl;
		for (int i = 0 ; i < params.size(); i++)
		{
			std::cout << params[i] << std::endl;
		}
	}
	/* Make executing strings */
	std::vector<std::string>	reVal;
	{
		if (tokens.size() > 1 && (tokens[1].at(0) == '#' || tokens[1].at(0) == '&'))
			reVal.push_back(tokens[1]);
		else
			reVal.push_back("MODE");
		std::vector<std::string>::iterator	flag_start = flag.begin();
		std::vector<std::string>::iterator	flag_end = flag.end();
		std::vector<std::string>::iterator	params_start = params.begin();
		std::vector<std::string>::iterator	params_end = params.end();
		for ( ; flag_start != flag_end; ++flag_start )
		{
			std::string::iterator	str_start = flag_start->begin();
			char	sign = *str_start;
			++str_start;
			std::string::iterator	str_end = flag_start->end();
			for ( ; str_start != str_end; ++str_start )
			{
				char flag = *str_start;
				if (flag == 'i' || flag == 't')
					reVal.push_back(MakeToken(sign, flag, ""));
				else if (sign == '-' && flag != 'o')
					reVal.push_back(MakeToken(sign, flag, ""));
				else if (sign == '+' && flag == 'l')
				{
					if (params_start != params_end && !IsDigit(*params_start))
						continue;
					if (params_start != params_end)
						reVal.push_back(MakeToken(sign, flag, *(params_start++)));
				}
				else
				{
					if (params_start != params_end)
						reVal.push_back(MakeToken(sign, flag, *(params_start++)));
				}
			}
		}
	}
	/* Make return string -> 
	execute functions must do it what stack data type */
	tokens = reVal;
	// for (int i = 0; i < reVal.size(); i++)
	// {
	// 	std::cout << reVal[i] << std::endl;
	// }
	if ( DEBUG )
		std::cout << "MODE parser off " << std::endl;
	return (0);
}
