#ifndef SUPERPARSER_HPP
# define SUPERPARSER_HPP

# include <iostream>
# include <vector>
# include <string>

class SuperParser
{
	private:
		SuperParser( SuperParser const &copy );
		SuperParser	&operator=( SuperParser const &copy );
		/* exceptions */
	protected:
		std::vector<std::string>	tokens;
		class ERR_NEEDMOREPARAMS : public std::exception
		{
			const char *what() const throw();
		};
	public:
		SuperParser( void );
		void			SetTokens( std::vector<std::string> token );
		virtual			~SuperParser( void );
		virtual int		CmdParser( void ) = 0;
};

#endif