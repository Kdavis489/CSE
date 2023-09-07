#include "servertcp.h"
#include "account.h"

int main()
{
	const int Port = 80;
	servertcp server;

	if (!server.InitNet() || !server.createSock() || !server.BindSock(Port) || !server.Listen() || !server.Accept())
	{
		return 1;
	}

	Account accountManager;

	std::thread(handleClients, std::ref(server), std::ref(accountManager));

	while (true)
	{

	}

		server.closeSock();
}