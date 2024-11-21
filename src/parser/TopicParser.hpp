/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:41:15 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/20 23:02:38 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPICPARSER_HPP
# define TOPICPARSER_HPP

#include "SuperParser.hpp"

class SuperParser;

class TopicParser : public SuperParser
{
	private:
		TopicParser( TopicParser const &copy );
		TopicParser	&operator=( TopicParser const &copy );
	protected:
	public:
		TopicParser( void );
		~TopicParser( void );
		int	CmdParser( void );
};

#endif