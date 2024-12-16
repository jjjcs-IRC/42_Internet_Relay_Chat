#include "Server.hpp"

Server *Server::m_instance = NULL; // 정적맴버 변수 초기화는 소스파일에서

Server::Server(int port, std::string password) : port(port), password(password), client_manager(ClientManager(password)), channelManager(ChannelManager()), numerics(client_manager, channelManager, serverInfo)
{
	m_serverSock = -1;
	m_kqueue = -1;
	m_changeIdx = 0;
	m_running = false;
	m_instance = this;
	m_changeList = new struct kevent[MAX_EVENTS];
	m_eventList = new struct kevent[MAX_EVENTS];

	// port하고 password 유효성 검사
	serverInfo.channelModes = "kost";
	serverInfo.serverName = "jjjcs_irc";
	serverInfo.datetime = "2024-11-22";
	serverInfo.tokens = "CHANNELLEN=32 NICKLEN=9 TOPICLEN=307";
	serverInfo.userModes = "io";
	serverInfo.version = "1.1";
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
	if (m_serverSock == -1)
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

	if (bind(m_serverSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) == -1)
	{
		std::cerr << "bind() error" << std::endl;
		exit(1);
	}
}

void Server::listenSocket(void)
{
	if (listen(m_serverSock, 5) == -1)
	{
		std::cerr << "listen() error" << std::endl;
		exit(1);
	}
}

void Server::createKqueue(void)
{
	m_kqueue = kqueue();
	if (m_kqueue == -1)
	{
		std::cerr << "kqueue() error" << std::endl;
		exit(1);
	}
}

void Server::registerServerSocket(void)
{
	EV_SET(&m_changeList[0], m_serverSock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	if (kevent(m_kqueue, &m_changeList[0], 1, NULL, 0, NULL) == -1)
	{
		std::cerr << "kevent() register error" << std::endl;
		exit(1);
	}
}

void Server::registerClientSocket(int clientSock)
{
	setNonBlocking(clientSock);

	EV_SET(&m_changeList[m_changeIdx], clientSock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	if (kevent(m_kqueue, &m_changeList[m_changeIdx], 1, NULL, 0, NULL) == -1)
	{
		std::cerr << "kevent() register error" << std::endl;
		return;
	}
	m_changeIdx = (m_changeIdx + 1) % MAX_EVENTS;

	m_clientSocks.push_back(clientSock);
}
void Server::registerClientWriteEvent(int clientSock)
{
	EV_SET(&m_changeList[m_changeIdx], clientSock, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	if (kevent(m_kqueue, &m_changeList[m_changeIdx], 1, NULL, 0, NULL) == -1)
	{
		std::cerr << "kevent() register error" << std::endl;
		return;
	}
	// m_changeIdx = (m_changeIdx + 1) % MAX_EVENTS;

}

void Server::unregisterWriteEvent(int clientSock)
{
	EV_SET(&m_changeList[m_changeIdx], clientSock, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
	if (kevent(m_kqueue, &m_changeList[m_changeIdx], 1, NULL, 0, NULL) == -1)
	{
		std::cerr << "kevent() unregister error" << std::endl;
		return;
	}
}


void Server::runServer(void)
{
	m_running = true;
	std::cout << "Server started. Waiting for connections..." << std::endl;

	struct timespec timeout;
	timeout.tv_sec = 5;
	timeout.tv_nsec = 0;

	while (m_running)
	{
		int n = kevent(m_kqueue, NULL, 0, m_eventList, MAX_EVENTS, &timeout);
		if (n == -1)
		{
			if (errno == EINTR)
				continue;
			std::cerr << "kevent() error" << std::endl;
			break;
		}

		if (!m_running)
			break;
		for (int i = 0; i < n; i++)
		{
			int eventFd = m_eventList[i].ident;
			if (eventFd == m_serverSock)
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

	int clientSock = accept(m_serverSock, (struct sockaddr *)&clientAddr, &clientAddrSize);
	if (clientSock == -1)
	{
		if (errno != EWOULDBLOCK)
			std::cerr << "accept() error" << std::endl;
		return;
	}
	std::cout << "New client connected: " << clientSock << std::endl;
	registerClientSocket(clientSock);

	// 클라이언트 객체 생성
	std::string ip = inet_ntoa(clientAddr.sin_addr);
	client_manager.add_client(clientSock, ip);
	std::cout << "new client obj is created" << std::endl;
}

void Server::handleClientData(int clientSock, struct kevent &event)
{
	if (event.flags & EV_EOF)
	{
		disconnectClient(clientSock);
		return;
	}
	else if (event.filter == EVFILT_READ)
	{
		const std::list<Client> &clientList = client_manager.get_clientList();
		unsigned long pos_crlf;
		std::string result;
		std::string tem_string;

		tem_string = client_manager.get_readBuf(clientSock);
		memset(read_buf, 0, BUF_SIZE);
		ssize_t strLen = read(clientSock, read_buf, BUF_SIZE);
		if (strLen <= 0)
		{
			disconnectClient(clientSock);
			return;
		}
		tem_string.append(read_buf);
		std::cout << "fd : " << clientSock << " input : " << read_buf << std::endl;
		if (tem_string.find("\r\n") == std::string::npos)
			client_manager.set_readBuf(clientSock, tem_string);
		else
			while ((tem_string.find("\r\n") != std::string::npos))
			{
				pos_crlf = tem_string.find("\r\n"); // 캐리지 리턴의 위치를 찾고
				result = tem_string.substr(0, pos_crlf); // result는 첫 위치부터 캐리지 리턴까지 저장
				tem_string.erase(0, pos_crlf + 2);		 // tem_string은 캐리지 리턴부터 끝까지 잘라서 저장
				client_manager.set_readBuf(clientSock, tem_string);
				if (result.length() == 0)
					continue;
				try
				{
					tParams res;

					parse.IrcParsing(clientSock, result, res);
					numerics.setParams(res); // 토큰에서 사용자의 입력값이 reply에 필요함
					if (res.tokens[0] == "PASS" && res.tokens.size() == 2 && res.tokens[1] != this->password)
						tem_string.clear(); // PASS의 비밀번호가 서버와 설정된것과 다르면, 같이 들어온 입력값을 초기화 시킴
					Command *command = CommandFactory::getInstance()->createCommand(res.cmd_type);
					std::cout << "before executeCommand : " << res.cmd_type << res.tokens[0] << std::endl;
					if (command != NULL)
						command->executeCommand(res, client_manager, channelManager);
					else{
						std::cout << "Unknown command" << res.cmd_type << res.tokens[0] << std::endl;
						throw 421;
					}
				}
				catch (int num)
				{
					numerics.dispatchByInt(clientSock, num);
				}
				for (std::list<Client>::const_iterator it = clientList.begin(); it != clientList.end(); it++)
				{
					int fd = it->get_clientFd(); // 각 리스트 객체의 fd값을 받아온다.
					if (client_manager.get_writeBuf(fd).length() > 0) //모든 fd의 write버퍼를 확인해서, 보낼게 있는지 확인
						registerClientWriteEvent(fd);
					// std::cout << "fd " << fd << " output |" << client_manager.get_writeBuf(fd) << std::endl;
					// write(fd, client_manager.get_writeBuf(fd).c_str(), client_manager.get_writeBuf(fd).length());
					// client_manager.set_writeBuf(fd, ""); // write buf를 clear함수를 쓸수 있게 하는 게 있으면 좋을듯
				}
			}
	}
	else if (event.filter == EVFILT_WRITE)
	{
		std::cout << "fd " << clientSock << " output |" << client_manager.get_writeBuf(clientSock) << std::endl;
		write(clientSock, client_manager.get_writeBuf(clientSock).c_str(), client_manager.get_writeBuf(clientSock).length());
		client_manager.set_writeBuf(clientSock, ""); // write buf를 clear함수를 쓸수 있게 하는 게 있으면 좋을듯
		unregisterWriteEvent(clientSock);
	}
}

void Server::disconnectClient(int clientSock)
{
	std::cout << "Client disconnected: " << clientSock << std::endl;
	Client* client=  client_manager.find_client(clientSock); //fd값으로 client 찾기
	const std::vector<std::string>& channels = client->get_channels(); // 크라이언트가 속한 채널 가져오기 
	const std::string clientName = client->get_nickName();
	
	for (size_t i = 0; i < channels.size(); ++i) { // 클라이언트가 속한 채널 돌면서 나오기
        const std::string channelName = channels[i];
		Channel* channel = channelManager.findChannel(channelName); // 채널이름으로 채널 찾기
		channel->removeParticipantByName(clientName); // 채널에서 유저 삭제

		if (channel->isOperator(client)) // 오퍼레이터이면 오퍼레이터 목록에서 삭제
        	channel->removeOperatorByName(clientName);
		
		if (channel->getParticipants().size() == 0) // 채널에 속한 사람수가 0명이면
			channelManager.deleteChannel(channelName); // 채널 삭제
		else{
			Client* frontParticipant =  channel->getParticipants().front(); // 채널에 속한 사람이 있으면
			channel->addOperator(frontParticipant); // 먼저 들어왔던 사람을 오퍼레이터로 임명
		}
    }

	client_manager.delete_client(clientSock);
	close(clientSock);

	/* 클라이언트 소켓 목록에서 제거 */
	std::vector<int>::iterator it;
	for (it = m_clientSocks.begin(); it != m_clientSocks.end(); ++it)
	{
		if (*it == clientSock)
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
	for (it = m_clientSocks.begin(); it != m_clientSocks.end(); ++it)
	{
		if (*it != -1)
		{
			close(*it);
			std::cout << "Closed client socket: " << *it << std::endl;
		}
	}
	m_clientSocks.clear();

	/* 서버 소켓 정리 */
	if (m_serverSock != -1)
	{
		close(m_serverSock);
		std::cout << "Closed server socket" << std::endl;
		m_serverSock = -1;
	}

	/* kqueue 정리 */
	if (m_kqueue != -1)
	{
		close(m_kqueue);
		std::cout << "Closed kqueue" << std::endl;
		m_kqueue = -1;
	}
}

std::string Server::receiveMessage(int clientSock)
{
	unsigned long pos_crlf;
	unsigned long pos_nl;
	std::string result;
	std::string tem_string;

	tem_string = client_manager.get_readBuf(clientSock);
	memset(read_buf, 0, BUF_SIZE);
	ssize_t strLen = read(clientSock, read_buf, BUF_SIZE);
	if (strLen <= 0)
	{
		disconnectClient(clientSock);
		return ("");
	}
	tem_string.append(read_buf);
	std::cout << "input result : " << read_buf << std::endl;
	printAsciiValues(read_buf);
	pos_crlf = tem_string.find("\r\n"); // 캐리지 리턴의 위치를 찾고
	pos_nl = tem_string.find("\n");

	if ((pos_crlf == std::string::npos) && (pos_nl == std::string::npos)) // 캐리지 리턴을 못 찾으면
	{
		printf("no cfrl nl\n");
		// tem_string.append(result, 0, result.length());
		// result.clear();
	}
	else if (pos_crlf < pos_nl)
	{
		// printf("cfrl\n");
		result = tem_string.substr(0, pos_crlf); // result는 첫 위치부터 캐리지 리턴까지 저장
		tem_string.erase(0, pos_crlf + 2);		 // tem_string은 캐리지 리턴부터 끝까지 잘라서 저장
	}
	else if (pos_crlf > pos_nl)
	{
		// printf("nl\n");
		result = tem_string.substr(0, pos_nl);
		tem_string.erase(0, pos_nl + 1);
	}
	// std::cout << "tem string : " << tem_string << std::endl;
	// std::cout << "result : " << result << std::endl;
	client_manager.set_readBuf(clientSock, tem_string);
	return (result);
}

// 임시 함수

void Server::printParams(tParams t_params)
{
	std::cout << "client fd : " << t_params.client_fd << std::endl;
	std::cout << "command type : " << t_params.cmd_type << std::endl;
	// std::cout << "password : " << t_params.password << std::endl;
	std::cout << "tokens : ";
	for (unsigned long i = 0; i < t_params.tokens.size(); i++)
	{
		std::cout << t_params.tokens[i] << " | ";
	}
	std::cout << "\n\n";
}

void Server::printAsciiValues(const std::string &str)
{
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		std::cout << *it << " -> " << static_cast<int>(*it) << std::endl;
	}
}
