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

int	ModeParser::IsFlag(char	c)
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

inline bool	ModeParser::IsSignString( std::string str )
{
	char	c;

	c = str.at(0);
	if (c == '+' || c == '-')
		return (true);
	return (false);
}

bool	ModeParser::Is_L_FlagConditions( std::string num )
{
	std::string::iterator	it = num.begin();
	std::string::iterator	end = num.end();
	for ( ; it != end ; ++it )
	{
		if (!std::isdigit(*it))
			return (false);
	}
	return (true);
}


// CMD
// options:sign:parameter
void	ModeParser::InitArr( std::string arr[][ARG_NUM] )
{
}

int	ModeParser::IsValidFlag( std::vector<std::string>	&flag, std::vector<std::string> &params )
{
	int	num = 0;
	int	k_sign = 0;

	{
		std::vector<std::string>::iterator	start = flag.begin();
		std::vector<std::string>::iterator	end = flag.end();
		for ( ; start != end ; ++start )
		{
			std::string::iterator	str_start = start->begin();
			char	sign = *str_start++;
			std::string::iterator	str_end = start->end();
			for ( ; str_start != str_end ; ++str_start )
			{
				if (*str_start == 'o')
					num++;
				if (*str_start == 'l' && sign == '+')
					num++;
				if (*str_start == 'k' && sign == '+')
					num++;
				if (*str_start == 'k' && sign == '-')
					k_sign++;
				if (IsFlag(*str_start) == false)
					throw (472 * 1000 + static_cast<int>(*str_start));
			}
		}
		if (num < params.size())
			throw (461);
	}
	return ( num );
}

int	ModeParser::CmdParser( void )
{
	if (tokens.size() < 2)
		throw (461);
	/* sorting strings(flag and parameters ) */
	std::vector<std::string>	flag;
	std::vector<std::string>	params;
	{
		std::vector<std::string>::iterator	start = tokens.begin();
		std::vector<std::string>::iterator	end = tokens.end();
		for ( ; start != end; ++start)
		{
			if (IsSignString(*start))
				flag.push_back(*start);
			else if (start != tokens.begin())
				params.push_back(*start);
		}
	}
	/* Is valid Number of parameters? */
	{
		IsValidFlag( flag, params );
	}
	/* Make executing strings */
	std::vector<std::string>	reVal;
	{

		reVal.push_back("MODE");
		std::vector<std::string>::iterator	flag_start = flag.begin();
		std::vector<std::string>::iterator	flag_end = flag.end();
		std::vector<std::string>::iterator	params_start = params.begin();
		std::vector<std::string>::iterator	params_end = params.end();
		for ( ; flag_start != flag_end; ++flag_start )
		{
			std::string::iterator	str_start = flag_start->begin();
			char	sign = *str_start;
			str_start++;
			std::string::iterator	str_end = flag_start->end();
			for ( ; str_start != str_end ; ++str_start )
			{
				char flag = *str_start;
				if (flag == 'i' || flag == 't')
					reVal.push_back(MakeToken(sign, flag, ""));
				else if (sign == '-' && flag != 'o')
					reVal.push_back(MakeToken(sign, flag, ""));
				else if (sign == '+' && flag == 'l')
				{
					if (!Is_L_FlagConditions(*params_start))
					{
						params_start++;
						continue;
					}
					reVal.push_back(MakeToken(sign, flag, *(params_start++)));
				}
				else
					reVal.push_back(MakeToken(sign, flag, *(params_start++)));
			}
		}
	}
	/* Make return string -> 
	execute functions must do it what stack data type */
	tokens = reVal;
	for (int i = 0; i < reVal.size(); i++)
	{
		std::cout << reVal[i] << std::endl;
	}
	return (0);
}
