#include "JjhangBot.hpp"

JjhangBot::JjhangBot( t_Arg	&arg ) : arg(arg)
{
	if (pthread_mutex_init(&arg.mutex_Ping, NULL) != 0)
	{
		std::exit(ERROR);
	}
	if (pthread_mutex_init(&arg.mutex_Time, NULL) != 0)
	{
		std::exit(ERROR);
	}
	if (pthread_mutex_init(&arg.mutex_bell, NULL) != 0)
	{
		std::exit(ERROR);
	}
	arg.bell = false;
	arg.ReadBuf[PING].push_back("PONG");
	std::cerr << "Done: Mutex initialized." << std::endl;
};

JjhangBot::~JjhangBot( void )
{
	pthread_mutex_destroy(&arg.mutex_bell);
	pthread_mutex_destroy(&arg.mutex_Ping);
	pthread_mutex_destroy(&arg.mutex_Time);
	std::cerr << "Call: Mutex destroy." << std::endl;
};

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
	std::string	Ping("PING I'm your BOT!\r\n");

	while ( true )
	{
		sign = false;

		LockMutex(data->mutex_Ping);
		data->ReadBuf[PING].clear();
		UnlockMutex(data->mutex_Ping);
		std::cerr << "sendMsg: " << Ping << std::endl;
		std::time_t	startTime = std::time(nullptr);
		SendToServer( data->socketFD, Ping );
		/* 5분동안 답신 대기*/
		std::time_t	curTime = startTime;
		std::cerr << "Wait: " << PING_TIME << " sec." << std::endl;
		while ( curTime - startTime < PING_TIME)
		{
			curTime = std::time(nullptr);
			usleep(1000);
			LockMutex(data->mutex_Ping);
			if (!data->ReadBuf[PING].empty() && data->ReadBuf[PING][0] == "PONG")
				sign = true;
			UnlockMutex(data->mutex_Ping);	
			/* 5분 대기 */
			if (sign == true)
			{
				LockMutex(data->mutex_bell);
				data->bell = true;
				UnlockMutex(data->mutex_bell);
				usleep(PING_TIME - (curTime - startTime));
			}
		}
		std::cerr << "PingTime: " << curTime - startTime << std::endl;
		std::cerr << "Recv: " << sign << std::endl;
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
	std::time_t now = std::time(nullptr);
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
	return (res);
}

void	JjhangBot::Time( t_Arg *data )
{
	bool	sign = false;
	while ( true )
	{
		LockMutex(data->mutex_bell);
		if ( data->bell == true )
			sign = true;
		UnlockMutex(data->mutex_bell);
		if (sign == true)
		{
			std::cerr << "Time: ERROR: Server Disconnected." << std::endl;
			exit (ERROR);
		}
		else
		{
			LockMutex(data->mutex_Time);
			if (data->ReadBuf[PRIVMSG].size() > 4 && data->ReadBuf[PRIVMSG][5] == "!TIME")
			{
				SendToServer( data->socketFD, Mksend(data->ReadBuf[PRIVMSG]));
				data->ReadBuf[PRIVMSG].clear();
			}
			UnlockMutex(data->mutex_Time);
		}
	}
}
void	*JjhangBot::execute( void *arg )
{
	t_Arg	*data = static_cast<t_Arg *>(arg);
	std::cout << "thread start: " << data->ThreadNum << std::endl;
	if (data->ThreadNum[PING] == PING)
			Ping( data );
	if (data->ThreadNum[PRIVMSG] == PRIVMSG)
		Time( data );
	return (data);
}

void	JjhangBot::CtlThread( int socketFD )
{
	this->thread = new(pthread_t[TH_NUM]);

	for (int i = 0; i < TH_NUM; i++)
	{
		arg.socketFD = socketFD;
		std::cout << "threads on [" << i << "]" << std::endl;
		arg.ThreadNum[i] = i;
		if (pthread_create(&thread[i], NULL, execute, static_cast<void *>(&arg)))
		{
			std::cerr << "Error: Failed to create thread" << std::endl;
			exit (1);
		}
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

}

void	JjhangBot::SendToServer( int socketFD, std::string const &msg )
{
	if (send(socketFD, msg.c_str(), msg.size(), 0) < 0)
	{
		std::cerr << "Error: Unable to send data: " << msg << std::endl;
	}
}

void	JjhangBot::ReadToServer( int socketFD, std::string &Readbuf )
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
				return ;
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
}

void	JjhangBot::Authenticate( int socketFD )
{
	// SendToserver(socketFD, "PASS " + password + "\r\n");
	SendToServer(socketFD, "NICK !TIME\r\n");
	SendToServer(socketFD, "USER TIME 0 * :JJHANG BOT IRC BOT\r\n");
	SendToServer(socketFD, "JOIN #newchat\r\n");
	/* JOIN */
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
	arg.ReadBuf[Type].insert(arg.ReadBuf[Type].begin(), Input.begin(), Input.end());
}

t_Arg	JjhangBot::getArg( void ) const
{
	return (arg);
}
