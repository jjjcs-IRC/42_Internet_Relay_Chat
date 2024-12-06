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
# define PRIVMSG 8
# define PONG 9
# define PING 10
# define PART 11

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

// template <typename T1, typename T2, typename T3>
// struct Triple {
//     T1 first;
//     T2 second;
//     T3 third;

//     // 생성자
//     Triple(const T1& first, const T2& second, const T3& third)
//         : first(first), second(second), third(third) {}
// };


#endif