#include "IrcParser.hpp"

IrcParser::IrcParser(void)
{
}

IrcParser::~IrcParser(void)
{
};

void	IrcParser::ShowParams( void )
{
	std::cout << std::endl << "==================================" << std::endl;
	std::cout << "Client_fd: " << data.client_fd << std::endl;
	std::cout << "CMD_Type : " << data.cmd_type << std::endl;
	std::cout << "== tokens ==" << std::endl;
	for (std::vector<std::string>::iterator it = data.tokens.begin(); it != data.tokens.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
	std::cout << std::endl << "==================================" << std::endl;
}

bool	IrcParser::IsValidString( std::string &CmdLine )
{
	/* options */
	if (CmdLine.empty())
		return (false);
	return (true);
}

tParams	IrcParser::IrcParsing( int fd, std::string &CmdLine )
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
		std::vector<std::string>				temp = split(line, ':');
		if (temp.size() > 2)
		{
			std::cerr << "invalid argument: Multiple colons" << std::endl;
			data.cmd_type = ERROR;
			return (data);
		}
		std::vector<std::string>::iterator		it = temp.begin();
		data.tokens = split(*it, ' ');
		std::cout << data.tokens.size() << std::endl;
		if (data.tokens.size() == 0)
		{
			std::cerr << "Error: there is no argument" << std::endl;
			data.cmd_type = ERROR;
			return (data);
		}
		if (temp.size() == 2)
		{
			line = *it++;
			data.tokens.push_back(':' + *it);
		}
		if (data.tokens.size() > 15)
		{
			std::cerr << "invalid argument: Too many arguments" << std::endl;
			data.cmd_type = ERROR;
			return (data);
		}
	}
	/* get CMD Type */
	data.cmd_type = GetCmdType(*data.tokens.begin());
	/* execute CmdParser */
	{
		SuperParser	*ptr;
		
		ptr = NewClassPtr( data.cmd_type );
		if (ptr == NULL)
		{
			data.cmd_type = ERROR;
			return (data);
		}
		ptr->SetTokens( data.tokens );
		if (ptr->CmdParser())
			data.cmd_type = ERROR;
		data.tokens = ptr->GetTokens();
		delete ptr;
	}
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
	return (ERROR);
}

SuperParser	*IrcParser::NewClassPtr( int type )
{
	if (type == PASS)
		return ( new PassParser() );
	if (type == NICK)
		return ( new NickParser() );
	if (type == USER)
		return ( new UserParser() );
	if (type == JOIN)
		return ( new JoinParser() );
	if (type == KICK)
		return ( new KickParser() );
	if (type == INVITE)
		return ( new InviteParser() );
	if (type == TOPIC)
		return ( new TopicParser() );
	if (type == MODE)
		return ( new ModeParser() );
	if (type == PRIVMSG)
		return ( new PrivParser() );
	return (NULL);
}