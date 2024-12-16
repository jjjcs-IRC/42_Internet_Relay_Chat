#include "IrcParser.hpp"

IrcParser::IrcParser(void)
{
}

IrcParser::~IrcParser(void)
{
};

bool	IrcParser::IsValidString( std::string &CmdLine )
{
	/* options */
	if (CmdLine.empty())
		return (false);
	return (true);
}

tParams	IrcParser::IrcParsing( int fd, std::string &CmdLine, tParams &data )
{
	data.client_fd = fd;
	/* check ValidString */
	if (!IsValidString( CmdLine ))
	{
		data.cmd_type = ERROR;
		return (data);
	}
	/* make t_params */
	{
		std::string								line(CmdLine);
		std::vector<std::string>				temp;
		const unsigned long	pos = line.find(':');
		if (pos != std::string::npos)
		{
			
			temp.push_back(line.substr(0, pos));
			temp.push_back(line.substr(pos + 1, line.size()));
		}
		else
		{
			temp.push_back(line);
		}
		std::vector<std::string>::iterator		it = temp.begin();
		data.tokens = split(*it, ' ');
		std::cout << "tokens_len: " << data.tokens.size() << std::endl;
		// std::cout << data.tokens.size() << std::endl;
		if (data.tokens.size() == 0)
		{
			std::cerr << "Error: there is no argument" << std::endl;
			data.cmd_type = ERROR;
		}
		*it++;
		if (it != temp.end())
			data.tokens.push_back(':' + *it);
	}
	/* get CMD Type */
	data.cmd_type = GetCmdType(*data.tokens.begin());
	return (data);
}

std::vector<std::string> IrcParser::split(const std::string& str, char delimiter)
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

int	IrcParser::GetCmdType( std::string &str )
{
	if (str == "PASS")
		return (PASS);
	else if (str == "NICK")
		return (NICK);
	else if (str == "USER")
		return (USER);
	else if (str == "JOIN")
		return (JOIN);
	else if (str == "KICK")
		return (KICK);
	else if (str == "INVITE")
		return (INVITE);
	else if (str == "TOPIC")
		return (TOPIC);
	else if (str == "MODE")
		return (MODE);
	else if (str == "PRIVMSG")
		return (PRIVMSG);
	else if (str == "PING")
		return (PONG);
	else if (str == "PONG")
		return (PING);
	else if (str == "PART")
		return (PART);
	return (ERROR);
}

void		IrcParser::ShowStatus( tParams &res )
{
	std::cout << "client_fd: " << res.client_fd << std::endl;
	std::cout << "cmd_type : " << res.cmd_type << std::endl;
	std::cout << "tokens_list: " << std::endl;
	for (unsigned long i = 0; i < res.tokens.size(); i++)
	{
		std::cout << "tokens[" << i << "]: " << res.tokens[i] << std::endl;
	}
	std::cout << "=============================" << std::endl;
}