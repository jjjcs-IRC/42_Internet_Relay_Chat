/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:41:17 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/20 18:51:23 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PassParser.hpp"

PassParser::PassParser( void )
{

}

PassParser::~PassParser( void )
{

}

bool	PassParser::CmdParser( void )
{
	if (tokens.size() > 2)
	{
		return (false);
	}
	std::cout << "*PASS PARSER TEST*" << std::endl;
	return (true);
}