#ifndef INVITEPARSER_HPP
# define INVITEPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

class InviteParser : public SuperParser
{
	private:
		InviteParser( InviteParser const &copy );
		InviteParser	&operator=( InviteParser const &copy );
	protected:
	public:
		InviteParser( void );
		~InviteParser( void );
		int	CmdParser( void );
};

#endif