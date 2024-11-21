/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcType.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyeuljhang <jaeyeuljhang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:18:45 by jaeyeuljhan       #+#    #+#             */
/*   Updated: 2024/11/21 18:46:26 by jaeyeuljhan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCTYPE_HPP
# define IRCTYPE_HPP

/* Irc Commands Type */
# define CMD_MAX 8 // Number of commands

# define ERROR -1
# define PASS 0
# define NICK 1
# define USER 2
# define JOIN 3
# define KICK 4
# define INVITE 5
# define TOPIC 6
# define MODE 7

/* abt fd value */
# define STDIN 0 // do not use
# define STDOUT 1 // do not use
# define STDERROR 2  // do not use
# define FD_MIN 3
# define FD_MAX 256

#ifndef S_PARAMS
# define S_PARAMS

#include <vector>

typedef struct sParams
{
	int							client_fd;
	int							cmd_type;
	std::vector<std::string>	tokens;
} tParams;
# endif

#endif