/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SuperParser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:15:09 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/20 18:54:59 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperParser.hpp"


SuperParser::SuperParser( void )
{

}

void	SuperParser::SetTokens( std::vector<std::string> token )
{
	this->tokens = token;
}


SuperParser::~SuperParser( void )
{

}
