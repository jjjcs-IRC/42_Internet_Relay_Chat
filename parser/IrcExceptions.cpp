/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcExceptions.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 02:26:28 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/20 17:26:17 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperParser.hpp"

const char	*SuperParser::ERR_NEEDMOREPARAMS::what() const throw()
{
	return (":Not enough parameters");
}