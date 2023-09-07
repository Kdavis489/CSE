#include "servertcp.h"

servertcp::servertcp() : serverSocket(INVALID_SOCKET)
{
}

servertcp::~servertcp()
{
}

bool servertcp::InitNet()
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

bool servertcp::createSock()
{
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		std::cerr << "Failed to create socket" << std::endl;
		return false;
	}

	std::cout << "Socket created successfully" << std::endl;
	return true;
}

bool servertcp::BindSock(int port)
{
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(Port);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		std::cerr << "Failed to bind to port: " << Port << std::endl;
		return false;
	}

	std::cout << "Successfully bound to port: " << Port << std::endl;
	return true;
}

bool servertcp::Listen()
{
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cerr << "Failed to Listen on port: " << Port << std::endl;
		return false;
	}

	std::cout << "Successfully listening on port: " << Port << std::endl;
	return true;
}

SOCKET servertcp::Accept()
{
	clientAddrSize = sizeof(clientAddr);
	clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cerr << "Failed to accept client" << std::endl;
		return INVALID_SOCKET;
	}

	std::cout << "Successfully accepted client" << std::endl;
	return clientSocket;
}

void servertcp::closeSock()
{
	closesocket(serverSocket);
#ifdef _WIN32
	WSACleanup();
#endif
}

void servertcp::handleClient(SOCKET clientSocket)
{
	while (true)
	{
		Account accountManager;
		std::thread([&]()
			{
				char buffer[1024];
				int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
				if (bytesRead > 0)
				{
					buffer[bytesRead] = '\0';
					std::string clientData(buffer);

					if (clientData.find("Create") == 0)
					{
						std::string username = clientData.substr(7);
						bool success = accountManager.AddAccount(username, "password");
						if (success)
						{
							send(clientSocket, "Account created successfully.", 27, 0);
						}
						else
						{
							send(clientSocket, "Failed to create Account", 24, 0);
						}
					}
					else
						if (clientData.find("Delete") == 0)
						{

						}
						else
							if (clientData.find("Login") == 0)
							{

							}
				}
				else
				{
					closesocket(clientSocket);
				}
			}).detach();
	}
}

void handleClients(servertcp& server, Account& accountManager)
{
	while (true)
	{
		SOCKET clientSocket = server.Accept();

		if (clientSocket == INVALID_SOCKET)  
		{
			continue;
		}

		std::thread(std::bind(&servertcp::handleClient, &server, clientSocket)).detach();
	}
}