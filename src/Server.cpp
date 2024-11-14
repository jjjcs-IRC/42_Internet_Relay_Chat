#include "Server.hpp"

Server* Server::m_instance = NULL; // 정적맴버 변수 초기화는 소스파일에서

Server::Server(int port, std::string password) : port(port), password(password)
{
	m_serverSock = -1;
    m_kqueue = -1;
    m_changeIdx = 0;
    m_running = false;
    m_instance = this;
    m_changeList = new struct kevent[MAX_EVENTS];
    m_eventList = new struct kevent[MAX_EVENTS];

	//port하고 password 유효성 검사
}

Server::~Server(void)
{
	cleanup();
    delete[] m_changeList;
    delete[] m_eventList;
}

void Server::signalHandler(int signo) 
{
    if (m_instance != NULL)
        m_instance->handleSignal(signo);
}

void Server::start(void)
{
    setupSignalHandlers();
    createSocket();
    setNonBlocking(m_serverSock);
    bindSocket(port);
    listenSocket();
    createKqueue();
    registerServerSocket();
    runServer();
}

void Server::handleSignal(int signo) 
{
    std::cout << "\nReceived signal " << signo << ". Shutting down..." << std::endl;
    m_running = false;
}

void Server::setupSignalHandlers() 
{
    signal(SIGINT, Server::signalHandler);
    signal(SIGTERM, Server::signalHandler);
}

void Server::setNonBlocking(int sock)
{
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}

void Server::createSocket(void) 
{
    m_serverSock = socket(PF_INET, SOCK_STREAM, 0);
    if(m_serverSock == -1)
	{
        std::cerr << "socket() error" << std::endl;
        exit(1);
    }
}

void Server::bindSocket(int port)
{
    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    if(bind(m_serverSock, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1)
	{
        std::cerr << "bind() error" << std::endl;
        exit(1);
    }
}

void Server::listenSocket(void)
{
    if(listen(m_serverSock, 5) == -1)
	{
        std::cerr << "listen() error" << std::endl;
        exit(1);
    }
}

void Server::createKqueue(void) 
{
    m_kqueue = kqueue();
    if(m_kqueue == -1)
	{
        std::cerr << "kqueue() error" << std::endl;
        exit(1);
    }
}

void Server::registerServerSocket(void) 
{
    EV_SET(&m_changeList[0], m_serverSock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    if(kevent(m_kqueue, &m_changeList[0], 1, NULL, 0, NULL) == -1)
	{
        std::cerr << "kevent() register error" << std::endl;
        exit(1);
    }
}

void Server::registerClientSocket(int clientSock) 
{
    setNonBlocking(clientSock);
    
    EV_SET(&m_changeList[m_changeIdx], clientSock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    if(kevent(m_kqueue, &m_changeList[m_changeIdx], 1, NULL, 0, NULL) == -1)
	{
        std::cerr << "kevent() register error" << std::endl;
        return;
    }
    m_changeIdx = (m_changeIdx + 1) % MAX_EVENTS;
    
    m_clientSocks.push_back(clientSock);
}

void Server::runServer(void) 
{
    m_running = true;
    std::cout << "Server started. Waiting for connections..." << std::endl;
    
    struct timespec timeout;
    timeout.tv_sec = 5;
    timeout.tv_nsec = 0;

    while(m_running)
	{
        int n = kevent(m_kqueue, NULL, 0, m_eventList, MAX_EVENTS, &timeout);
        if(n == -1)
		{
            if(errno == EINTR)
				continue;
            std::cerr << "kevent() error" << std::endl;
            break;
        }
        
        if(!m_running)
			break;
        for(int i = 0; i < n; i++)
		{
            int eventFd = m_eventList[i].ident;
            if(eventFd == m_serverSock)
                handleNewConnection();
			else
                handleClientData(eventFd, m_eventList[i]);
        }
    }
}

void Server::handleNewConnection(void) 
{
    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    
    int clientSock = accept(m_serverSock, (struct sockaddr*)&clientAddr, &clientAddrSize);
    if(clientSock == -1)
	{
        if(errno != EWOULDBLOCK)
            std::cerr << "accept() error" << std::endl;
        return;
    }
    std::cout << "New client connected: " << clientSock << std::endl;
    registerClientSocket(clientSock);

	// 클라이언트 객체 생성
	// 클라이언트 객체를 생성하는 매니저 클래스의 함수 필요
	client_manager.add_client(clientSock);
	std::cout << "new client obj is created" << std::endl;
}

void Server::handleClientData(int clientSock, struct kevent& event) 
{
    if(event.flags & EV_EOF)
	{
        disconnectClient(clientSock);
        return;
    }
    memset(read_buf, 0, BUF_SIZE);
    ssize_t strLen = read(clientSock, read_buf, BUF_SIZE);
    if(strLen <= 0)
	{
        disconnectClient(clientSock);
        return;
    }

	//PASS, NICK, USER
	// std::cout << read_buf << std::endl;
	parse_cmd(clientSock);



    write(clientSock, write_buf, strLen);
}

void Server::disconnectClient(int clientSock) 
{
    std::cout << "Client disconnected: " << clientSock << std::endl;
    close(clientSock);
    
    /* 클라이언트 소켓 목록에서 제거 */
    std::vector<int>::iterator it;
    for(it = m_clientSocks.begin(); it != m_clientSocks.end(); ++it)
	{
        if(*it == clientSock)
		{
            m_clientSocks.erase(it);
            break;
        }
    }
}

void Server::cleanup(void) 
{
    std::cout << "Performing cleanup..." << std::endl;
    
    /* 클라이언트 소켓 정리 */
    std::vector<int>::iterator it;
    for(it = m_clientSocks.begin(); it != m_clientSocks.end(); ++it)
	{
        if(*it != -1)
		{
            close(*it);
            std::cout << "Closed client socket: " << *it << std::endl;
        }
    }
    m_clientSocks.clear();
    
    /* 서버 소켓 정리 */
    if(m_serverSock != -1)
	{
        close(m_serverSock);
        std::cout << "Closed server socket" << std::endl;
        m_serverSock = -1;
    }
    
    /* kqueue 정리 */
    if(m_kqueue != -1)
	{
        close(m_kqueue);
        std::cout << "Closed kqueue" << std::endl;
        m_kqueue = -1;
    }
}



//////////////////////////////////////////////// server_cmd
std::vector<std::string>	Server::parse_cmd(int fd)
{
	std::vector<std::string>	params;

	params = split(read_buf, ' ');
	// std::cout << params.size() << std::endl;
	params[0].erase(std::remove(params[0].begin(), params[0].end(), '\n'), params[0].end()); // 클라에서 입력된 패스워드에 개행 제거 
	if (params[0] == "PASS" && params.size() == 2)
	{
		params[1].erase(std::remove(params[1].begin(), params[1].end(), '\n'), params[1].end()); // 클라에서 입력된 패스워드에 개행 제거 
		if (this->password == params[1])
		{
			client_manager.pass_client(fd);
			std::cout << "pass password" << std::endl;
		}
	}
	else if (params[0] == "NICK" && params.size() == 2)
	{
		params[1].erase(std::remove(params[1].begin(), params[1].end(), '\n'), params[1].end()); // 클라에서 입력된 패스워드에 개행 제거 
		client_manager.set_nick_client(fd, params[1]);
		std::cout << "set nickname" << std::endl;
	}
	else if (params[0] == "USER" && params.size() == 2)
	{
		params[1].erase(std::remove(params[1].begin(), params[1].end(), '\n'), params[1].end()); // 클라에서 입력된 패스워드에 개행 제거 
		client_manager.set_real_client(fd, params[1]);
		std::cout << "set realname" << std::endl;
	}
	if (params[0] == "NICK" && params.size() == 1)
	{
		std::cout << "print NICK" << std::endl;
		memset(write_buf, 0, BUF_SIZE);
		send(fd, client_manager.print_client(fd).c_str(), client_manager.print_client(fd).length(), 0);
	}
	return (params);
}
