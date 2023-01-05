#include "main.h"


int main()
{
	SocketNetwork::Server MainServer;
	MainServer.Open(10000);
	MainServer.Run();
	//MainServer.Connect("192.168.0.122", 10000);

	while (1)
	{
		std::string msg;
		std::cin >> msg;

		if (msg == "exit")
		{
			MainServer.Close();
			break;
		}

		MainServer.Send(msg);
	}

	MainServer.Close();
	return 0;
}