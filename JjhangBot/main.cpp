#include "JjhangBot.hpp"

bool	IsServerFormat( std::string &str )
{
	int	num = 0;

	if (str.size() > 15)
		return (false);
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '.')
			num++;
	}
	if (num != 3)
		return (false);
	return (true);
}

bool	IsPortFormat( std::string &str )
{
	for(int i = 0; i < str.size(); i ++)
	{
		if (!std::isdigit(str[i]))
			return (false);
	}
	return (true);
}

int	main( int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cerr << "Must follow the format: <Server> <Port> <Server Password>" << std::endl;
		return (-1);
	}
	JjhangBot	Bot;
	std::string	server(argv[1]);
	int			port;

	t_Arg		*arg = Bot.InitThread();
	Bot.SetArg(arg);
	if (!IsServerFormat(server))
	{
		std::cerr << "Must follow the format: Server: xxx.xxx.xxx.xxx." << std::endl;
		return (-1);
	}
	std::string	temp(argv[2]);
	if (!IsPortFormat(temp))
	{
		std::cerr << "Must follow the format: <Port>" << std::endl;
		return (-1);
	}
	port = std::atoi( argv[2] );
	int	fd;
	fd = Bot.ConnectToServer( argv[1], port );
	std::string password( argv[3] );
	Bot.SendToServer(fd, "PASS " + password + "\r\n" );
	Bot.Authenticate( fd );
	Bot.CtlThread( fd );
	{
		std::string		ReadBuf;
		IrcBotParser	parser;
		std::vector<std::string>	data;
		while ( true )
		{
			Bot.ReadToServer( fd, ReadBuf );
			parser.IrcParsing( ReadBuf, data );
			if (!data.empty() && data[0] == "PING")
			{
				std::cout << "Ping Parser Done" << std::endl;
				Bot.LockMutex(*arg[PING].mutex_Ping);
				Bot.InputString(PING, data);
				Bot.UnlockMutex(*arg[PING].mutex_Ping);
				std::cout << "Ping execute Done" << std::endl;
			}
			else if (!data.empty() && data.size() > 3 && data[2] == "PRIVMSG")
			{
				std::cout << "Privmsg Parser Done" << std::endl;
				Bot.LockMutex(*arg[PRIVMSG].mutex_Time);
				Bot.InputString(PRIVMSG, data);
				Bot.UnlockMutex(*arg[PRIVMSG].mutex_Time);
				std::cout << "Privmsg execute Done" << std::endl;
			}
		}

	}
	Bot.JoinThread();
	Bot.DeleteThrad( arg );
	return (0);
}

// int	main( void )
// {
// 	/* tester */
// 	t_Arg	arg;
// 	JjhangBot Bot(arg);


// 	// Bot.Ping(&arg);
// 	// std::cout << "set read buf" << std::endl;
// 	// arg.ReadBuf[PRIVMSG].push_back("Name");
// 	// arg.ReadBuf[PRIVMSG].push_back("!~adf@host");
// 	// arg.ReadBuf[PRIVMSG].push_back("PRIVMSG");
// 	// arg.ReadBuf[PRIVMSG].push_back("me");
// 	// arg.ReadBuf[PRIVMSG].push_back(":TIME");
// 	// std::cout << "set done" << std::endl;
// 	// Bot.Time(&arg);
// 	/* parser test */
// 	// IrcBotParser parser;
// 	// std::string					str1("PONG #^dfjkdfljkvz dfaskljf 23");
// 	// std::vector<std::string>	vec1;
	
// 	// vec1.clear();
// 	// parser.IrcParsing(str1, vec1);
// 	// std::string					str2(":SenderNick!~user@host PRIVMSG TargetNick :Hello, how are you?");
// 	// std::vector<std::string>	vec2;
	
// 	// vec2.clear();
// 	// parser.IrcParsing(str2, vec2);

// 	return (0);
// }