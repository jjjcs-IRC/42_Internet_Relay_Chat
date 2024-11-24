#ifndef MODEPARSER_HPP
# define MODEPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

# define FLAG 0
# define SIGN 1
# define ARG 2

# define iFlag 0
# define tFlag 1
# define kFlag 2
# define oFlag 3
# define lFlag 4

# define FLAG_NUM 5
# define ARG_NUM 3

class ModeParser : public SuperParser
{
	private:
		ModeParser( ModeParser const &copy );
		ModeParser	&operator=( ModeParser const &copy );
		std::string	MakeToken( std::string flag, std::string sign, std::string param );
		int			IsFlag(char c);
		inline bool	IsSignString( std::string str );
		void		InitArr( std::string arr[][ARG_NUM] );
		std::vector<std::string>	ModeParsing( std::vector<std::string>::iterator &it );
	protected:
	public:
		ModeParser( void );
		~ModeParser( void );
		int	CmdParser( void );
};

#endif