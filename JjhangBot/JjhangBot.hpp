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

# define PING_TIME 30
typedef struct s_Arg
{
	int	socketFD;
	int	ThreadNum;
	std::vector<std::string>	*ReadBuf;
	pthread_mutex_t	*mutex_Ping;
	pthread_mutex_t	*mutex_Time;
} t_Arg;

class JjhangBot
{
	private:
		pthread_t	*thread;
		t_Arg		*arg;
		const char	*server;
		int			port;
		int			socketFD;
		
		std::string serverName;


		JjhangBot( JjhangBot const &copy );
		JjhangBot &operator=( JjhangBot const &copy );
	protected:
	public:
		/* O.C.C.F */
		JjhangBot( void );
		~JjhangBot( void );

		/* Functions */
		static void Time( t_Arg *data );
		static void	Ping( t_Arg *data );
		void		SetArg( t_Arg *data );

		/* About Server */
		int	ConnectToServer( const char *server, int port );
		void	Authenticate( int socketFD, std::string const &PassWord );
		static void	SendToServer(int sock, std::string const &msg );
		static void	ReadToServer( int socketFD, std::string &Readbuf );

		/* About Threads */
		t_Arg	*InitThread( void );
		void	DeleteThrad( t_Arg *arg );
		static void	*execute( void *arg );
		void	CtlThread( int socketFD );
		void	JoinThread( void );
		static void	LockMutex( pthread_mutex_t &mutex );
		static void	UnlockMutex( pthread_mutex_t &mutex );
		void	InputString( int Type, std::vector<std::string>	&Input );
		
		/* Utiles */
		t_Arg	getArg( void ) const;
};

#endif