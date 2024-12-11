#ifndef PARENTPARSER_HPP
# define PARENTPARSER_HPP

# include <iostream>
# include <vector>
# include <string>

class ParentParser
{
	private:
		ParentParser( ParentParser const &copy );
		ParentParser	&operator=( ParentParser const &copy );
		/* exceptions */
	protected:
		std::vector<std::string>	tokens;
	public:
		ParentParser( void );
		void			SetTokens( std::vector<std::string> &token );
		std::vector<std::string> GetTokens( void ) const;
		virtual			~ParentParser( void );
		virtual int		CmdParser( void ) = 0;
};

#endif