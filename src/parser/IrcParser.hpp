/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:37:58 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/20 21:36:09 by jimchoi          ###   ########.fr       */
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