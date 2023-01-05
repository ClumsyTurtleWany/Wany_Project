#include "SocketNetwork.h"

bool SocketNetwork::StartUp()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return false;
	}

	return true;
}

bool SocketNetwork::CleanUp()
{
	WSACleanup();
	return true;
}

bool SocketNetwork::OpenSocket(SocketEx& target, ProtocolType protocol)
{
	//SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	target.Protocol = protocol;
	if (protocol == ProtocolType::TCP)
	{
		target.Socket = socket(AF_INET, SOCK_STREAM, 0);
	}
	else if (protocol == ProtocolType::UDP)
	{
		target.Socket = socket(AF_INET, SOCK_DGRAM, 0);
	}

	return true;
}

bool SocketNetwork::Connect(SocketEx& target, std::string ip, int port)
{
	target.IP = ip;
	target.Port = port;
	target.Addr.sin_family = AF_INET;
	target.Addr.sin_addr.s_addr = inet_addr(ip.c_str());
	target.Addr.sin_port = htons(port);

	int rst = connect(target.Socket, (sockaddr*)&target.Addr, sizeof(target.Addr));
	if (rst == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

bool SocketNetwork::Bind(SocketEx& target, int port)
{
	target.Port = port;
	target.Addr.sin_family = AF_INET;
	target.Addr.sin_addr.s_addr = htonl(INADDR_ANY);
	target.Addr.sin_port = htons(port);

	int rst = bind(target.Socket, (sockaddr*)&target.Addr, sizeof(target.Addr));
	if (rst == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

bool SocketNetwork::Listen(SocketEx& target)
{
	int rst = listen(target.Socket, SOMAXCONN);
	if (rst == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

SocketNetwork::SocketEx* SocketNetwork::Accept(SocketEx& host)
{
	SocketEx* Client = new SocketEx;
	int length = sizeof(SOCKADDR_IN);
	Client->Socket = accept(host.Socket, (sockaddr*)&Client->Addr, &length);
	if (Client->Socket == SOCKET_ERROR)
	{
		delete Client;
		Client = nullptr;
		return nullptr;
	}

	return Client;
}

bool SocketNetwork::Send(SocketEx& target, std::string& msg)
{
	int length = msg.size();
	int SendBytes = send(target.Socket, msg.c_str(), length, 0);
	if (SendBytes == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			return false;
		}
	}

	return true;
}

bool SocketNetwork::Receive(SocketEx& target, std::string& msg)
{
	char buffer[256] = { 0, };
	int length = 256;
	int ReceiveBytes = recv(target.Socket, buffer, length, 0);
	if (ReceiveBytes == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			return false;
		}
	}

	int ReceiveMsgLength = ReceiveBytes / sizeof(char);
	for (int i = 0; i < ReceiveMsgLength; i++)
	{
		msg.push_back(buffer[i]);
	}

	return true;
}

bool SocketNetwork::CloseSocket(SocketEx& target)
{
	closesocket(target.Socket);
	return true;
}

void SocketNetwork::SetBlock(SocketEx& target)
{
	u_long Mode = TRUE;
	ioctlsocket(target.Socket, FIONBIO, &Mode);
}

void SocketNetwork::SetNonBlock(SocketEx& target)
{
	u_long Mode = FALSE;
	ioctlsocket(target.Socket, FIONBIO, &Mode);
}

