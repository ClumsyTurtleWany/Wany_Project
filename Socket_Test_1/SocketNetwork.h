#pragma once
#pragma comment(lib, "Ws2_32.lib") 

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <thread>
#include <vector>

namespace SocketNetwork
{
	typedef enum class ProtocolType
	{
		TCP,
		UDP,
	};

	

	typedef struct ClientInfo
	{
		SOCKET Socket;
		SOCKADDR_IN Addr;
	};

	typedef struct ThreadInfo
	{
		SOCKET Host;
		ClientInfo Client;
	};

	class Client
	{
	private:
		int _Port;
		std::string _IP;

	public:
		Client(std::string ip, int port);
		~Client();

	protected:
		bool initialize();
		bool run();
		bool pause();
		bool stop();
		bool release();
	};


	class Host
	{
	private:
		int Port = 0;
		ProtocolType Protocol;

		WSADATA Wsa;
		SOCKET MainSocket;
		SOCKADDR_IN MainSockAddr;


		HANDLE AcceptThreadHandle;
		HANDLE RunEventHandle;
		HANDLE ExitEventHandle;

		std::vector<ClientInfo*> ClientList;

	public:
		Host(int port, ProtocolType protocol = ProtocolType::TCP);
		~Host();

	protected:
		bool initialize();
		bool release();

	protected:
		bool addClient(SOCKET socket, SOCKADDR_IN addr);

	public:
		bool run();
		bool pause();
		bool stop();

		static DWORD WINAPI AcceptThread(LPVOID lpParam);
		static DWORD WINAPI ReceiveThread(LPVOID lpParam);
	};
}