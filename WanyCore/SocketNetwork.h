#pragma once
//#pragma comment(lib, "Ws2_32.lib") 
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//
//#include <WinSock2.h>
//#include <WS2tcpip.h>
//#include <string>
//#include <thread>
//#include <vector>
//#include <map>
#include "Define.hpp"

namespace SocketNetwork
{
	////////////////////////////////////////////////////////////////////////////////////////
	// Typedef
	////////////////////////////////////////////////////////////////////////////////////////

	typedef enum class ProtocolType
	{
		TCP,
		UDP,
	};

	typedef struct SocketEx
	{
		std::string		IP;
		int				Port;
		bool			isConnected = false;
		ProtocolType	Protocol;
		SOCKET			Socket;
		SOCKADDR_IN		Addr;
	};

	////////////////////////////////////////////////////////////////////////////////////////
	// Common Function
	////////////////////////////////////////////////////////////////////////////////////////
	
	// Start Up/Clean Up Socket Network
	bool StartUp();
	bool CleanUp();

	// Open/Close Socket;
	bool OpenSocket(SocketEx& target, ProtocolType protocol = ProtocolType::TCP);
	bool CloseSocket(SocketEx& target);

	// Client
	bool Connect(SocketEx& target, std::string ip, int port);

	// Host
	bool Bind(SocketEx& target, int port);
	bool Listen(SocketEx& target);
	SocketEx* Accept(SocketEx& host); // Return Client Socket Pointer

	// Mesagge
	bool Send(SocketEx& target, std::string& msg, int length);
	bool Receive(SocketEx& target, std::string& msg, int length);

	void SetBlock(SocketEx& target);
	void SetNonBlock(SocketEx& target);

	////////////////////////////////////////////////////////////////////////////////////////
	// Server Base
	////////////////////////////////////////////////////////////////////////////////////////

	// Thread Based
	class Server
	{
	protected:
		typedef struct ReceiveThreadInfo
		{
			Server* HostServer;
			SocketEx* Client;
		};

	protected:
		SocketEx HostSocket;
		std::map<std::string, SocketEx*> HostList;
		std::map<std::string, SocketEx*> ClientList;

		bool isOpen = false;

		HANDLE ExitEventHandle = NULL;
		HANDLE AcceptThreadHandle = NULL;

	public:
		Server();
		virtual ~Server();

	protected:
		virtual bool Initialize();
		virtual bool Release();

	public:
		virtual bool Open(int port, ProtocolType protocol = ProtocolType::TCP);
		virtual bool Close();
		virtual bool Connect(std::string name, std::string ip, int port);
		virtual bool Run();
		virtual bool SendMsgToHost(std::string name, std::string& msg, int length);
		virtual bool SendMsgToClient(std::string name, std::string& msg, int length);
		virtual bool SendMsgToHostAll(std::string& msg, int length);
		virtual bool SendMsgToClientAll(std::string& msg, int length);
		virtual bool SendMsgToAll(std::string& msg, int length);
		virtual bool RunAcceptThread();
		virtual bool RunClientReceiveThread(SocketEx* client);
		virtual bool AddClient(SocketEx* client);

	protected:
		static DWORD WINAPI AcceptThread(LPVOID lpParam);
		static DWORD WINAPI ReceiveThread(LPVOID lpParam);
	};
}