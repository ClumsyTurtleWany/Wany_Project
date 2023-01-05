#include "main.h"


int main()
{
	ChatServer MainServer;
	MainServer.Open(10000);
	MainServer.Run();
	//MainServer.Connect("192.168.0.122", 10000);

	while (1)
	{
		system("cls");
		for (auto it = MainServer.MsgLog.begin(); it != MainServer.MsgLog.end(); it++)
		{
			std::cout << *it << std::endl;
		}

		/*std::string msg;
		std::cin >> msg;

		if (msg == "exit")
		{
			MainServer.Close();
			break;
		}*/

		//MainServer.SendMsgToClientAll(msg, msg.size());
		Sleep(1000);
	}

	MainServer.Close();
	return 0;
}