/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:41:15 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/21 17:01:22 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JoinPARSER_HPP
# define JoinPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

class JoinParser : public SuperParser
{
	private:
		JoinParser( JoinParser const &copy );
		JoinParser	&operator=( JoinParser const &copy );
	protected:
	public:
		JoinParser( void );
		~JoinParser( void );
		int	CmdParser( void );
};

#endif