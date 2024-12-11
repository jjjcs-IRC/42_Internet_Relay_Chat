#ifndef JJHANGBOT_HPP
# define JJHANGBOT_HPP

# include <iostream>
# include <string>
# include <cstdlib>
# include <unistd.h>
# include <ctime>

# include <sys/socket.h> // socket API
# include <netinet/in.h> // Internet address protocol
# include <arpa/inet.h> // ip address exchanger

# include "IrcBotParser.hpp"

# define PING_TIME 300
typedef struct s_Arg
{
	int	socketFD;
	int	ThreadNum[TH_NUM];
	std::vector<std::string>	ReadBuf[TH_NUM];
	pthread_mutex_t	mutex_bell;
	bool			bell;
	pthread_mutex_t	mutex_Ping;
	pthread_mutex_t	mutex_Time;
} t_Arg;

class JjhangBot
{
	private:
		pthread_t	*thread;
		t_Arg		&arg;
		const char	*server;
		int			port;
		int			socketFD;
		
		std::string serverName;
		JjhangBot( JjhangBot const &copy );
		JjhangBot &operator=( JjhangBot const &copy );
		static void	*execute( void *arg );
		JjhangBot( void );
	protected:
	public:
		static void Time( t_Arg *data );
		static void	Ping( t_Arg *data );
		JjhangBot( t_Arg &arg );
		~JjhangBot( void );
		int	ConnectToServer( const char *server, int port );
		void	Authenticate( int socketFD );
		static void	SendToServer(int sock, std::string const &msg );
		static void	ReadToServer( int socketFD, std::string &Readbuf );
		void	CtlThread( int socketFD );
		void	JoinThread( void );
		static void	LockMutex( pthread_mutex_t &mutex );
		static void	UnlockMutex( pthread_mutex_t &mutex );
		void	InputString( int Type, std::vector<std::string>	&Input );
		t_Arg	getArg( void ) const;
};

#endif