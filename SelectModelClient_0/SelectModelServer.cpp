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

	int rst = WSAAsyncSelect(HostSocket.Socket, m_hWnd, WM_USER_NETWORK_MSG, FD_ACCEPT | FD_READ | FD_WRITE | FD_CLOSE | FD_CONNECT);
	if (rst == SOCKET_ERROR)
	{
		return false;
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