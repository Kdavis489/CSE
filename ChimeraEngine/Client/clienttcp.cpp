#include "clienttcp.h"

clienttcp::clienttcp() : clientSocket(INVALID_SOCKET)
{
}

bool clienttcp::InitNet()
{
#ifdef _WIN32
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "Failed to initialize winsock" << std::endl;
		return false;
	}
#endif
	createSock();
	std::cout << "Winsock Initialized" << std::endl;
	return true;
}

bool clienttcp::createSock()
{
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cerr << "Failed to create socket" << std::endl;
		return false;
	}

	std::cout << "Socket created successfully" << std::endl;
	return true;
}

bool clienttcp::Connect()
{
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(Port);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		std::cerr << "Failed to connect to server" << std::endl;
			closeSock();
			return 1;
	}

	std::cout << "Connected to server" << std::endl;
	return true;
}

void clienttcp::closeSock()
{
	closesocket(clientSocket);
#ifdef _WIN32
	WSACleanup();
#endif
}
