#pragma once

#ifdef _WIN32
#define WIN_32_LEAN_AND_MEAN
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#define socklen_t int
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SOCKET int
#define INVALID_SOCKET -1
#define closesocket close
#define SOCKET_ERROR -1
#endif
#include "account.h"
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <thread>

class servertcp
{
public:
	servertcp();
	~servertcp();

	const int Port = 80;

	bool InitNet();
	bool createSock();
	bool BindSock(int port);
	bool Listen();
	SOCKET Accept();
	void closeSock();
	void handleClient(SOCKET clientSocket);
private:
	SOCKET serverSocket;
	SOCKET clientSocket;
	WSADATA wsaData;
	sockaddr_in serverAddr;
	sockaddr_in clientAddr;
	int clientAddrSize;
//	char buffer[1024];
//	char buffer2[4096];
};


void handleClients(servertcp& server, Account& accountManager);