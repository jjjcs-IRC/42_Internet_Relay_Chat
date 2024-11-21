/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:41:15 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/21 18:46:17 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEPARSER_HPP
# define MODEPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

class ModeParser : public SuperParser
{
	private:
		ModeParser( ModeParser const &copy );
		ModeParser	&operator=( ModeParser const &copy );
	protected:
	public:
		ModeParser( void );
		~ModeParser( void );
		int	CmdParser( void );
};

#endif