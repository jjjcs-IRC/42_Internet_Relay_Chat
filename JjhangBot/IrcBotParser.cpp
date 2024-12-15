#include "IrcBotParser.hpp"

IrcBotParser::IrcBotParser(void)
{
}

IrcBotParser::~IrcBotParser(void)
{
};

bool	IrcBotParser::IsValidString( std::string &CmdLine )
{
	/* options */
	if (CmdLine.empty())
		return (false);
	return (true);
}

std::vector<std::string>	IrcBotParser::IrcParsing( std::string &CmdLine, std::vector<std::string> &data )
{
	/* check ValidString */
	if (!IsValidString( CmdLine ))
		return (data);
	/* make t_params */
	{
		std::string								line;
		if (!CmdLine.empty() && CmdLine.size() > 0 && CmdLine[0] == ':')
			line = CmdLine.substr(1, std::strlen(CmdLine.c_str()) - 1);
		else
			line = CmdLine;
		std::vector<std::string>				temp;
		size_t	pos = line.find(':');
		if ( pos != std::string::npos )
		{
			temp.push_back( line.substr(0, pos) );
			temp.push_back( line.substr( pos + 1, line.size() ) );
		}
		else
		{
			temp.push_back(line);
		}
		std::vector<std::string>::iterator		it = temp.begin();
		data = split(*it, ' ');
		// std::cout << data.tokens.size() << std::endl;
		if (data.size() == 0)
			std::cerr << "Error: there is no argument" << std::endl;
		*it++;
		if (it != temp.end())
			data.push_back(':' + *it);
	}
	/* get CMD Type */
	/* execute CmdParser */
	{
		int	cmdType = GetCmdType(data);
		ParentParser	*ptr;
		
		ptr = NewClassPtr( cmdType );
		if (ptr == NULL)
			return (data);
		ptr->SetTokens( data );
		ptr->CmdParser();
		data = ptr->GetTokens();
		delete ptr;
	} 
	std::cout << "MAIN PROCESS" << std::endl;
	ShowStatus(data);
	return (data);
}

std::vector<std::string> IrcBotParser::split(const std::string& str, char delimiter)
{
	std::vector<std::string>	tokens;
	std::stringstream			ss(str);
	std::string					token;

	while (std::getline(ss, token, delimiter))
	{
		if (!token.empty())
		{
			tokens.push_back(token);
			token.clear();
		}
	}
	return (tokens);
}

int	IrcBotParser::GetCmdType( std::vector<std::string> &vec )
{
	if (vec.size() > 1 && vec[1] == "PONG")
		return (PING);
	else if (vec.size() > 1 && vec[1] == "PRIVMSG")
		return (PRIVMSG);
	return (ERROR);

}

ParentParser	*IrcBotParser::NewClassPtr( int type )
{
	if (type == PING)
		return ( new PingParser() );
	if (type == PRIVMSG)
		return ( new PrivParser() );
	return (NULL);
}

void	IrcBotParser::ShowStatus( std::vector<std::string> &vec )
{
	std::cout << "Vector's Status" << std::endl;
	for ( unsigned int i = 0; i < vec.size(); i++ )
	{
		std::cout << "[" << i << "]: " << vec[i] << std::endl;
	}
}