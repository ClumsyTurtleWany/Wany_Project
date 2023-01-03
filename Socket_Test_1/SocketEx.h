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

	class SocketEx
	{
	private:
		SOCKET Socket;

	public:
		SocketEx();
		~SocketEx();

	public:
		// Client
		bool Connect(std::string ip, int port);

		// Host
		bool Bind(int port);
		bool Accept(SOCKET& socket, SOCKADDR_IN& addr);

		// Common
		bool Send(SOCKET socket, const char* buffer, int length);
		bool Receive(SOCKET socket, char* buffer, int length);

		void SetBlock();
		void SetNonBlock();
	};
}