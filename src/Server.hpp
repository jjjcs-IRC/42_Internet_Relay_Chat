#ifndef	SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/event.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#include "ClientManager.hpp"
#include <string>
#include <sstream>

const int BUF_SIZE = 1024; // 전역변수가 됬나?
const int MAX_EVENTS = 30;

class Server {
	private :

		int	port; // port가 유효한지에 대한 함수 필요
		std::string password; // password가 유효한지에 대한 함수 필요

		ClientManager client_manager;

		int m_serverSock;           /* 서버 소켓 파일 디스크립터 */
		int m_kqueue;              /* kqueue 파일 디스크립터 */
    	struct kevent* m_changeList; /* 감시할 이벤트 목록 */
    	struct kevent* m_eventList;  /* 발생한 이벤트 목록 */
    	int m_changeIdx;           /* change_list 배열의 현재 인덱스 */
    
    /* 데이터 송수신 관련 변수 */
    	char read_buf[BUF_SIZE];    /* 메시지 버퍼 */
		char write_buf[BUF_SIZE];
    	std::vector<int> m_clientSocks; /* 연결된 클라이언트 소켓 목록 */
    
    /* 서버 상태 관련 변수 */
    	bool m_running;             /* 서버 실행 상태 플래그 */
    	static Server* m_instance;  /* 시그널 핸들러에서 사용할 인스턴스 포인터 */

	public :
		Server(int port, std::string password);
		~Server(void);

		static void signalHandler(int signo);
		void start(void);

	private :
		void handleSignal(int signo);
		void setupSignalHandlers(void);
		void setNonBlocking(int sock);
		void createSocket(void);
		void bindSocket(int port);
		void listenSocket(void);
		void createKqueue(void);
		void registerServerSocket(void);
		void registerClientSocket(int clientSock);
		void runServer(void);
		void handleNewConnection(void);
		void handleClientData(int clientSock, struct kevent& event);
		void disconnectClient(int clientSock);
		void cleanup(void);

		//server측 command
		public :
		std::vector<std::string> parse_cmd(int fd);
		std::vector<std::string> split(const std::string& str, char delimiter) {
    		std::vector<std::string> tokens;
    		std::stringstream ss(str);
    		std::string token;

    		while (std::getline(ss, token, delimiter)) {
    		    tokens.push_back(token);
    		}
    		return tokens;
		}
};

#endif