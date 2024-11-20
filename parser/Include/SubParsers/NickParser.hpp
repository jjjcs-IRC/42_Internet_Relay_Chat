/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:41:15 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/20 18:51:51 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICKPARSER_HPP
# define NICKPARSER_HPP

#include "SuperParser.hpp"

class	SuperParser;

class NickParser : public SuperParser
{
	private:
		NickParser( NickParser const &copy );
		NickParser	&operator=( NickParser const &copy );
	protected:
	public:
		NickParser( void );
		~NickParser( void );
		bool	CmdParser( void );
};

#endif