#ifndef TOPICPARSER_HPP
# define TOPICPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

class TopicParser : public SuperParser
{
	private:
		TopicParser( TopicParser const &copy );
		TopicParser	&operator=( TopicParser const &copy );
	protected:
	public:
		TopicParser( void );
		~TopicParser( void );
		int	CmdParser( void );
};

#endif