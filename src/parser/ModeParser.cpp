#include "ModeParser.hpp"

ModeParser::ModeParser( void )
{

}

ModeParser::~ModeParser( void )
{

}

std::string	ModeParser::MakeToken( std::string flag, std::string sign, std::string param )
{
	return (flag + ':' + sign + ':' + param);
}

int	ModeParser::IsFlag(char	c)
{
	if ('i' == c)
		return (iFlag);
	if ('t' == c)
		return (tFlag);
	if ('k' == c)
		return (kFlag);
	if ('o' == c)
		return (oFlag);
	if ('l' == c)
		return (lFlag);
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


// CMD
// options:sign:parameter
void	ModeParser::InitArr( std::string arr[][ARG_NUM] )
{
	arr[iFlag][FLAG] = "i";
	arr[iFlag][SIGN] = "X";
	arr[tFlag][FLAG] = "t";
	arr[tFlag][SIGN] = "X";
	arr[kFlag][FLAG] = "k";
	arr[kFlag][SIGN] = "X";
	arr[oFlag][FLAG] = "o";
	arr[oFlag][SIGN] = "X";
	arr[lFlag][FLAG] = "l";
	arr[lFlag][SIGN] = "X";
}

int	ModeParser::CmdParser( void )
{
	if (tokens.size() < 2)
		throw (461);
	std::string	arr[FLAG_NUM][ARG_NUM];
	InitArr(arr);
	std::vector<std::string>::iterator it = tokens.begin();
	if (*it == "MODE")
		++it;
	for ( ; it != tokens.end(); ++it )
	{
		if ((*it)[0] == '+' || (*it)[0] == '-')
		{
			char sign = (*it)[0];
			std::vector<std::string>::iterator	temp = it++;
			std::string::iterator ait = temp->begin();
			std::string::iterator end = temp->end();
			++temp;
			for (; ait != end; ait++ )
			{
				char	flag = (*ait);
				int	flagNum = IsFlag(flag);
				arr[flagNum][SIGN] = sign;
				if (sign == '+' && flag == 'k')
				{
					arr[flagNum][ARG] = *temp;
					temp++;
				}
				if (sign == '-' && flag == 'k')
					arr[flagNum][ARG] = "";
				if (sign == '+' && flag == 'l')
				{
					arr[flagNum][ARG] = *temp;
					temp++;
				}
				if (sign == '-' && flag == 'l')
					arr[flagNum][ARG] = "";
				if (sign == '+' && flag == 'o')
				{
					arr[flagNum][ARG] += *temp;
					temp++;
				}
				if (sign == '-' && flag == 'o')
					arr[flagNum][ARG] = "";
			}
		}
	}
	std::vector<std::string> newAnswer(5);
	for (int i = 0; i < FLAG_NUM; i++)
	{
		std::cout << arr[i][FLAG] << ":" << arr[i][SIGN] << ":" << arr[i][ARG] <<std::endl;
		newAnswer[i] = MakeToken(arr[i][FLAG], arr[i][SIGN], arr[i][ARG]);
	}
	tokens = newAnswer;
	return (0);
}
