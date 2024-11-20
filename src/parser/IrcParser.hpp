/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:37:58 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/20 20:54:03 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef IRCPARSER_HPP
# define IRCPARSER_HPP

# include <iostream>
# include <string>
# include <vector>
# include <sstream>
# include <cctype>
# include <exception>
# include "IrcType.hpp"

/* Child Class Header */
# include "SuperParser.hpp"
# include "PassParser.hpp"
# include "NickParser.hpp"
# include "UserParser.hpp"


#ifndef S_PARAMS
# define S_PARAMS

typedef struct sParams
{
	int							client_fd;
	int							cmd_type;
	std::vector<std::string>	tokens;
} tParams;
# endif


class IrcParser
{
	protected:
		/* parameter manager */
		SuperParser	*ptr;
		tParams	data;
	private :
		/* Do not use this constructer and operator: Only for OCCF */
		IrcParser( IrcParser const &copy );
		IrcParser 	&operator=( IrcParser const &copy );

		/* private functions */
		bool		IsValidString( std::string &CmdLine );
		std::vector<std::string> split(const std::string& str, char delimiter);
		int			GetCmdType( std::string &str );
		SuperParser	*NewClassPtr( int type );
	public :
		/* OCCF */
		IrcParser( void );
		~IrcParser( void );

		/* for DEBUG */
		void			ShowParams( void );
		/* public function */
		tParams		IrcParsing( int fd, std::string &CmdLine );
};

#endif