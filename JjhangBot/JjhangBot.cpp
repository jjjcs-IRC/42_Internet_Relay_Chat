#include "JjhangBot.hpp"

JjhangBot::JjhangBot( void )
{
	thread = new pthread_t[TH_NUM];
};

JjhangBot::~JjhangBot( void )
{
	delete [] thread;
};

t_Arg	*JjhangBot::InitThread( void )
{
	t_Arg	*res;
	
	res = new t_Arg[TH_NUM];
	res->ReadBuf = new std::vector<std::string>[TH_NUM];
	res->mutex_Ping = new pthread_mutex_t;
	res->mutex_Time = new pthread_mutex_t;

	for (int i = 0; i < TH_NUM; i++)
	{
		res[i].ThreadNum = i;
		res[i].mutex_Ping = res->mutex_Ping;
		res[i].mutex_Time = res->mutex_Time;
	}
	res[PRIVMSG].ReadBuf = res->ReadBuf;

	return (res);
}

void	JjhangBot::DeleteThrad( t_Arg *arg )
{
	delete arg->mutex_Ping;
	delete arg->mutex_Time;

	delete [] arg->ReadBuf;
	delete [] arg;
}

int	JjhangBot::ConnectToServer( const char *server, int port )
{
	sockaddr_in	serverAddr;

	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFD < 0)
	{
		std::cerr << "Error: Unable to create socket" << std::endl;
		exit (ERROR);
	}
	std::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	if(inet_pton(AF_INET, server, &serverAddr.sin_addr) <= 0)
	{
		std::cerr << "Error: Invalid server address" << std::endl;
		close(socketFD);
		exit (ERROR);
	}
	if (connect(socketFD, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		std::cerr << "Error: Unable to connect to server!" << std::endl;
		close (socketFD);
		exit (ERROR);
	}
	return (socketFD);
};

void	JjhangBot::Ping( t_Arg *data )
{
	bool		sign = false;
	std::string	Ping("PING I'm_your_BOT!\r\n");

	while ( true )
	{
		sign = false;

		LockMutex(*data->mutex_Ping);
		data->ReadBuf[PING].clear();
		UnlockMutex(*data->mutex_Ping);
		std::cerr << "sendMsg: " << Ping << std::endl;
		std::time_t	startTime = std::time(NULL);
		SendToServer( data->socketFD, Ping );
		/* 5분동안 답신 대기*/
		std::time_t	curTime = startTime;
		std::cerr << "Wait: " << PING_TIME << " sec." << std::endl;
		while ( curTime - startTime < PING_TIME)
		{
			curTime = std::time(NULL);
			usleep(1000);
			LockMutex(*data->mutex_Ping);
			if (!data->ReadBuf[PING].empty() && data->ReadBuf[PING].size() > 1 && data->ReadBuf[PING][1] == "PONG")
			{
				std::cout << "received PONG" <<std::endl;
				sign = true;
			}
			data->ReadBuf[PING].clear();
			UnlockMutex(*data->mutex_Ping);	
			/* 5분 대기 */
			if (sign == true)
			{
				usleep(PING_TIME - (curTime - startTime));
			}
		}
		if (sign == false)
		{
			std::cerr << "Notification: Unable to receive Pong." << std::endl;
			std::exit(ERROR);
		}
	}
}

std::string	Mksend( std::vector<std::string> &tokens )
{
	std::string	res;

	res = "PRIVMSG ";
	if (tokens[3][0] == '#')
		res += tokens[3];
	else
		res += tokens[0];
	res += " :Today is ";
	std::time_t now = std::time(NULL);
	std::tm *localTime = std::localtime(&now);
	std::ostringstream	ss;
	ss << (localTime->tm_year + 1900) << "-";
	ss << (localTime->tm_mon + 1) << "-";
	ss << localTime->tm_mday << " ";
	ss.fill('0');
	ss.width(2);
	ss << localTime->tm_hour << ":";
	ss.width(2);
	ss << localTime->tm_min << ":";
	ss.width(2);
	ss << localTime->tm_sec;
	res += ss.str();
	res += "\r\n";
	std::cerr << "return string: " << res;
	return (res);
}

void	JjhangBot::Time( t_Arg *data )
{
	bool	sign = false;
	while ( true )
	{
		if (sign == true)
		{
			std::cerr << "Time: ERROR: Server Disconnected." << std::endl;
			exit (ERROR);
		}
		else
		{
			LockMutex(*data->mutex_Time);
			if (!data->ReadBuf[PRIVMSG].empty())
			{
				std::cout << data->ReadBuf[PRIVMSG][4].c_str() << std::endl;
			}
			if (data->ReadBuf[PRIVMSG].size() > 3 && !std::strncmp(data->ReadBuf[PRIVMSG][4].c_str(), ":!TIME", 6))
			{
				SendToServer( data->socketFD, Mksend(data->ReadBuf[PRIVMSG]));
			}
			data->ReadBuf[PRIVMSG].clear();
			UnlockMutex(*data->mutex_Time);
			usleep(100);
		}
	}
}

void	*JjhangBot::execute( void *arg )
{
	t_Arg	*data = (t_Arg *)(arg);
	std::cout << "Thread start" << std::endl;
	std::cout << "Thread num is " << data->ThreadNum << std::endl;
	usleep(1000);
	if (data->ThreadNum == PING)
	{
		std::cout << "PING start" << std::endl;
		Ping( data );
	}
	if (data->ThreadNum == PRIVMSG)
	{
		std::cout << "TIME start" << std::endl;
		Time( data );
	}
	return (data);
}

void	JjhangBot::CtlThread( int socketFD )
{
	for (int i = 0; i < TH_NUM; i++)
	{
		arg[i].socketFD = socketFD;
		std::cout << "threads on [" << i << "]" << std::endl;
		arg[i].ThreadNum = i;
	}
	if (pthread_create(&thread[PING], NULL, execute, static_cast<void *>(&arg[PING])))
	{
		std::cerr << "Error: Failed to create thread" << std::endl;
		exit (1);
	}
	if (pthread_create(&thread[PRIVMSG], NULL, execute, static_cast<void *>(&arg[PRIVMSG])))
	{
		std::cerr << "Error: Failed to create thread" << std::endl;
		exit (1);
	}
}

void	JjhangBot::JoinThread( void )
{
	for (int i = 0; i < TH_NUM; i++)
	{
		pthread_join(this->thread[i], NULL);
		std::cout << "thread off" << std::endl;
	}
	delete [] this->thread;
	delete [] arg->ReadBuf;

}

int	JjhangBot::SendToServer( int socketFD, std::string const &msg )
{
	int	res;

	res = send(socketFD, msg.c_str(), msg.size(), 0);
	if (res < 0)
	{
		std::cerr << "Error: Unable to send data: " << msg << std::endl;
	}
	return (res);
}

int	JjhangBot::ReadToServer( int socketFD, std::string &Readbuf )
{
	char	buffer[1024];
	
	Readbuf = "";
	while (true)
	{
		std::memset(buffer, 0, 1024);
		ssize_t	bytesRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0);
		if (bytesRead > 0)
		{
			size_t	pos;

			buffer[bytesRead] = '\0';
			Readbuf += std::string(buffer);
			
			pos = Readbuf.find('\n');
			if (pos != std::string::npos)
				return(ERROR);
		}
		else if (bytesRead == 0)
		{
			std::cerr << "Server disconnected." << std::endl;
			exit (1);
		}
		else if (bytesRead < 0)
		{
			std::cerr << "Error: reading from server." << std::endl;
		}
	}
	std::cout << "Server: " << Readbuf << std::endl;
	return (0);
}

void	JjhangBot::Authenticate( int socketFD, std::string const &PassWord )
{
	int							sign = 1;
	std::string					ReadBuf;
	std::vector<std::string>	vec;
	std::string					bot("bot");
	IrcBotParser				parser;
	
	while ( sign )
	{
		SendToServer(socketFD, PassWord + "NICK " + bot + "\r\nUSER bot 0 * :JJHANG IRC BOT\r\n");
		usleep(1000);
		ReadToServer(socketFD, ReadBuf);
		parser.IrcParsing(ReadBuf, vec);
		parser.ShowStatus(vec);
		if (vec.size() > 2 && vec[1] == "432")
		{
			bot = "bot";
			bot = bot + static_cast<char>(sign);
		}
		else
			break ;
		sign++;
	}
	usleep(1000);
}

void	JjhangBot::LockMutex( pthread_mutex_t &mutex )
{
	pthread_mutex_lock(&mutex);
}

void	JjhangBot::UnlockMutex( pthread_mutex_t &mutex )
{
	pthread_mutex_unlock(&mutex);
}
void	JjhangBot::InputString( int Type, std::vector<std::string>	&Input )
{
	arg->ReadBuf[Type].insert(arg->ReadBuf[Type].begin(), Input.begin(), Input.end());
}

t_Arg	JjhangBot::getArg( void ) const
{
	return (*arg);
}

void	JjhangBot::SetArg( t_Arg *data )
{
	this->arg = data;
}