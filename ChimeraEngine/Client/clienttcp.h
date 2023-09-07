#pragma once

#pragma once

#ifdef _WIN32
#define WIN_32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <WS2tcpip.h>
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

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <thread>

class clienttcp
{
public:
	clienttcp();
	~clienttcp();
	bool InitNet();
	bool createSock();
	bool Connect();
	void closeSock();
private:
	WSADATA wsaData;
	SOCKET serverSocket;
	SOCKET clientSocket;
	sockaddr_in serverAddr;
	sockaddr_in clientAddr;
	int serverAddrSize;
	const int Port = 80;
	std::string serverIP = "127.0.0.1";
};