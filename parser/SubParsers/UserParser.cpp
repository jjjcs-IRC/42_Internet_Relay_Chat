/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:41:17 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/20 18:49:04 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserParser.hpp"

UserParser::UserParser( void )
{

}

UserParser::~UserParser( void )
{

}

bool	UserParser::CmdParser( void )
{
	if (tokens.size() > 2)
		return (false);
	return (true);
}