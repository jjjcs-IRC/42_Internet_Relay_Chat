// #ifndef JOIN_HPP
// # define JOIN_HPP

// #include "Command.hpp"



// class Join : public Command {

// 	public :
// 		Join();
// 		~Join();
// 		virtual int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn);

// 	private :
// 		Join(const Join &other);
// 		Join* operator=(const Join &other);


// };


// #endif

#ifndef JOIN_HPP
# define JOIN_HPP

#include "../parser/IrcType.hpp"  // tParams 정의를 가져오기 위해
#include "Command.hpp"

class Join : public Command {
    public:
        Join();
        ~Join();
        virtual int executeCommand(tParams &params, ClientManager &cl, ChannelManager &cn);

    private:
        Join(const Join &other);
        Join& operator=(const Join &other);
};

#endif