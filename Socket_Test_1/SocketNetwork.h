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

	typedef struct SocketEx
	{
		std::string		IP;
		int				Port;
		ProtocolType	Protocol;
		SOCKET			Socket;
		SOCKADDR_IN		Addr;
	};

	// Open Socket;
	bool OpenSocket(SocketEx& target, ProtocolType protocol = ProtocolType::TCP);

	// Client
	bool Connect(SocketEx& target, std::string ip, int port);

	// Host
	bool Bind(SocketEx& target, int port);
	bool Accept(SocketEx& host, SocketEx& client);

	// Common
	bool Send(SocketEx& target, std::string& msg);
	bool Receive(SocketEx& target, std::string& msg);
	bool Close(SocketEx& target);

	void SetBlock(SocketEx& target);
	void SetNonBlock(SocketEx& target);

	class Server
	{
	public:
		typedef struct ReceiveThreadInfo
		{
			Server* HostServer;
			SocketEx* Client;
		};

	private:
		SocketEx SelfHost;
		std::vector<SocketEx*> HostList;
		std::vector<SocketEx*> ClientList;

		bool isOpen = false;

		HANDLE ExitEventHandle;
		HANDLE AcceptThreadHandle = NULL;

	public:
		Server();
		~Server();

	public:
		bool Open(int port, ProtocolType protocol = ProtocolType::TCP);
		bool Connect(std::string ip, int port);
		bool Run();
		bool Send(std::string& msg);
		bool Close();

	private:
		bool AddClient(SocketEx* client);
		bool SendToHost(std::string& msg);
		bool SendToClient(std::string& msg);

	private:
		static DWORD WINAPI AcceptThread(LPVOID lpParam);
		static DWORD WINAPI ReceiveThread(LPVOID lpParam);
		static DWORD WINAPI SendThread(LPVOID lpParam);
	};
}