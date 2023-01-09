#include "ChatServer.h"

bool ChatServer::Open(HWND hWnd)
{
	int rst = WSAAsyncSelect(HostSocket.Socket, hWnd, WM_USER_NETWORK_MSG, FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
	if (rst == SOCKET_ERROR)
	{
		return false;
	}
	
	isOpen = true;
	return true;
}

bool ChatServer::Run()
{
	if (!isOpen)
	{
		return false;
	}

	return true;
}

bool ChatServer::AddClient(SocketNetwork::SocketEx* client)
{
	return false;
}
