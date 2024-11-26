/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:41:15 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/20 18:51:53 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASSPARSER_HPP
# define PASSPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

class PassParser : public SuperParser
{
	private:
		PassParser( PassParser const &copy );
		PassParser	&operator=( PassParser const &copy );
	protected:
	public:
		PassParser( void );
		~PassParser( void );
		bool	CmdParser( void );
};

#endif