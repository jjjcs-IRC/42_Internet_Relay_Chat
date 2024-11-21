/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:41:17 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/21 18:10:36 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InviteParser.hpp"

InviteParser::InviteParser( void )
{

}

InviteParser::~InviteParser( void )
{

}

int	InviteParser::CmdParser( void )
{
	if (tokens.size() < 3)
		throw (461);
	return (0);
}