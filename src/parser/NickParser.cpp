/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:41:17 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/21 01:02:01 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickParser.hpp"

NickParser::NickParser( void )
{
	
}

NickParser::~NickParser( void )
{

}

int	NickParser::CmdParser( void )
{
	if (tokens.size() == 1)
		throw (431);
	return (0);
}