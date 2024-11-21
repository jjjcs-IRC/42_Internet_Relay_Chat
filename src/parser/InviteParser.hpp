/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:41:15 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/20 23:02:38 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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