/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:41:17 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/20 18:51:17 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickParser.hpp"

NickParser::NickParser( void )
{
	
}

NickParser::~NickParser( void )
{

}

bool	NickParser::CmdParser( void )
{
	if (tokens.size() > 2)
		return (false);
	return (true);
}