/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:41:15 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/20 18:54:02 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERPARSER_HPP
# define USERPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

class UserParser : public SuperParser
{
	private:
		UserParser( UserParser const &copy );
		UserParser	&operator=( UserParser const &copy );
	protected:
	public:
		UserParser( void );
		~UserParser( void );
		bool	CmdParser( void );
};

#endif