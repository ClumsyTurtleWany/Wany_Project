#include "SelectModelServer.h"

SocketNetwork::SelectModelServer::SelectModelServer(HWND hWnd)
	:m_hWnd(hWnd)
{
}

SocketNetwork::SelectModelServer::~SelectModelServer()
{
}

bool SocketNetwork::SelectModelServer::Run()
{
	if (!isOpen)
	{
		return false;
	}

	FD_ZERO(&m_rSet);
	FD_ZERO(&m_wSet);
	FD_SET(HostSocket.Socket, &m_rSet);
	FD_SET(HostSocket.Socket, &m_wSet);
	for (auto& it : ClientList)
	{
		FD_SET((*it.second).Socket, &m_rSet);
		FD_SET((*it.second).Socket, &m_wSet);
	}

	timeval time;
	time.tv_sec = 0;
	time.tv_usec = 1000; // 1 mili Sec
	int rst = select(0, &m_rSet, &m_wSet, NULL, &time);
	if (rst == SOCKET_ERROR)
	{
		return false;
	}

	if (rst == 0)
	{
		return false;
	}

	if (FD_ISSET(HostSocket.Socket, &m_rSet))
	{
		SocketEx* Client = SocketNetwork::Accept(HostSocket);
		if (Client != nullptr)
		{
			AddClient(Client);
		}
	}

	for (auto& it : ClientList)
	{
		SocketEx* Client = it.second;
		if (FD_ISSET(Client->Socket, &m_wSet))
		{
			std::string msg;
			SocketNetwork::SetNonBlock(*Client);
			if (SocketNetwork::Receive(*Client, msg, 255))
			{
				ReceiveMsg(msg);
			}
			int a = 0;
		}
	}

	return true;
}

bool SocketNetwork::SelectModelServer::AddClient(SocketEx* client)
{
	if (client == nullptr)
	{
		return false;
	}

	client->IP = inet_ntoa(client->Addr.sin_addr);
	client->Port = ntohs(client->Addr.sin_port);

	std::string name = client->IP + ":" + std::to_string(client->Port);
	ClientList.insert(std::make_pair(name, client));

	return true;
}

bool SocketNetwork::SelectModelServer::AcceptClient()
{
	SocketNetwork::SocketEx* newClient = SocketNetwork::Accept(HostSocket);
	if (newClient == nullptr)
	{
		return false;
	}

	AddClient(newClient);

	return true;
}

bool SocketNetwork::SelectModelServer::CloseClient(SOCKET sock)
{
	for (auto& it : ClientList)
	{
		SocketEx* ClientSocket = it.second;
		if (ClientSocket == nullptr)
		{
			continue;
		}

		if (ClientSocket->Socket == sock)
		{
			SocketNetwork::CloseSocket(*ClientSocket);
			ClientList.erase(it.first);
			break;
		}
	}
	return true;
}

bool SocketNetwork::SelectModelServer::ReceiveFromClient(SOCKET sock, std::string& msg)
{
	for (auto& it : ClientList)
	{
		SocketEx* ClientSocket = it.second;
		if (ClientSocket == nullptr)
		{
			continue;
		}

		if (ClientSocket->Socket == sock)
		{
			SocketNetwork::Receive(*ClientSocket, msg, 255);
			return true;
		}
	}
	return false;
}