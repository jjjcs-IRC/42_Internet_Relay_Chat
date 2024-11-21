/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:41:17 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/21 18:46:24 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ModeParser.hpp"

ModeParser::ModeParser( void )
{

}

ModeParser::~ModeParser( void )
{

}

int	ModeParser::CmdParser( void )
{
	if (tokens.size()  == 5) // The variable must be number 5
		throw (461);
	if (tokens[4][0] != ':') // The last variable must start with ':'
		throw (461);
	return (0);
}