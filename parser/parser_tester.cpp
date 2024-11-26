/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:46:08 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/20 18:56:51 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcParser.hpp"

int	main(void)
{
	IrcParser test;
	std::string	input = "   PASS  abc "; // put the case;
	tParams	res;
	
	res = test.IrcParsing(3, input);
	test.ShowParams();
	
	return (0);
}