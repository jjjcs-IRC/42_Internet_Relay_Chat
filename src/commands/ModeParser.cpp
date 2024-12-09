#include "Mode.hpp"

static std::string	MakeToken( char flag, char sign, std::string param )
{
	return (std::string(1, flag) + ":" + std::string(1, sign) + ":" + param);
}

static int	IsFlag(char	c)
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

static inline bool	IsSignString( std::string &str )
{
	char	c;

	c = str.at(0);
	if (c == '+' || c == '-')
		return (true);
	return (false);
}

static int	IsValidFlag( std::string &flag )
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

bool	IsDigit( std::string str )
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

std::vector<std::string>	Mode::Parser( std::vector<std::string>	&tokens )
{
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
	/* Make executing strings */
	std::vector<std::string>	reVal;
	{
		reVal.push_back("MODE");
		if (tokens.size() > 1)
			reVal.push_back(tokens[1]);
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
	return (tokens);
}
