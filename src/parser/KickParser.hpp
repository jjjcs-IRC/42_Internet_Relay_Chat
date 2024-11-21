/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickParser copy.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:41:15 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/21 18:42:11 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KICKPARSER_HPP
# define KICKPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

class KickParser : public SuperParser
{
	private:
		KickParser( KickParser const &copy );
		KickParser	&operator=( KickParser const &copy );
	protected:
	public:
		KickParser( void );
		~KickParser( void );
		int	CmdParser( void );
};

#endif