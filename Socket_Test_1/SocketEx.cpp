#include "SocketEx.h"

SocketNetwork::SocketEx::SocketEx()
{
}

SocketNetwork::SocketEx::~SocketEx()
{
}

bool SocketNetwork::SocketEx::Connect(std::string ip, int port)
{
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	addr.sin_port = htons(port);

	int rst = connect(Socket, (sockaddr*)&addr, sizeof(addr));
	if (rst == SOCKET_ERROR)
	{
		return false;
	}
	
	return true;
}

bool SocketNetwork::SocketEx::Bind(int port)
{
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	int rst = bind(Socket, (sockaddr*)&addr, sizeof(addr));
	if (rst == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

bool SocketNetwork::SocketEx::Accept(SOCKET& socket, SOCKADDR_IN& addr)
{
	SetBlock();
	int length = sizeof(SOCKADDR_IN);
	socket = accept(Socket, (sockaddr*)&addr, &length);
	SetNonBlock();
	if (socket == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

bool SocketNetwork::SocketEx::Send(SOCKET socket, const char* buffer, int length)
{
	int SendBytes = send(socket, buffer, length, 0);
	if (SendBytes == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			return false;
		}
	}

	return true;
}

bool SocketNetwork::SocketEx::Receive(SOCKET socket, char* buffer, int length)
{
	int ReceiveBytes = recv(socket, buffer, length, 0);
	if (ReceiveBytes == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			return false;
		}
	}

	return true;
}

void SocketNetwork::SocketEx::SetBlock()
{
	u_long Mode = TRUE;
	ioctlsocket(Socket, FIONBIO, &Mode);
}

void SocketNetwork::SocketEx::SetNonBlock()
{
	u_long Mode = FALSE;
	ioctlsocket(Socket, FIONBIO, &Mode);
}
