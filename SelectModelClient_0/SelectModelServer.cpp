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

	if (0) // 매 프레임 돌릴 것.
	{
		HANDLE ListenEvent = WSACreateEvent(); // 통신에도 API처럼 이벤트가 있지만 수동 리셋 이벤트만 있다.
		HANDLE m_EventList[64];
		m_EventList[0] = ListenEvent; // 0번에 넣어준 이유는 WSAWaitForMultipleEvents의 반환값이 가장 작은 인덱스를 반환하기 때문에
		WSAEventSelect(HostSocket.Socket, ListenEvent, FD_ACCEPT); // 이벤트를 소켓에 바인딩 하여 사용 가능.
		DWORD dwIndex = WSAWaitForMultipleEvents(ClientList.size() + 1, m_EventList, FALSE, 0, FALSE); // 이벤트가 발생한 이벤트 인덱스 반환 해 줌. 만약 이벤트가 동시에 발생하면 가장 앞의 인덱스값만 반환 된다.
		if (dwIndex == WSA_WAIT_FAILED)
		{
			return false;
		}

		if (dwIndex == WSA_WAIT_TIMEOUT)
		{
			return false;
		}

		dwIndex = dwIndex - WSA_WAIT_EVENT_0; // 이벤트의 시작 위치를 빼줌.
		if (dwIndex == 0) // m_EventList[0]에 Host 소켓 + FD_ACCEPT 바인딩 해 줬으니 0번이 반환되면 호스트에서 할 것 처리
		{
			// Event List에 Accept를 바인딩 했으므로 Accept 처리.
			WSANETWORKEVENTS networkEvent;
			int rst = WSAEnumNetworkEvents(HostSocket.Socket, m_EventList[dwIndex], &networkEvent);
			if (rst == SOCKET_ERROR)
			{
				return false;
			}

			if (networkEvent.lNetworkEvents & FD_ACCEPT)
			{
				// networkEvent에 발생한 이벤트를 받아와서 FD_ACCEPT와 같으면 Accept를 처리하면 된다.
			}
		}

		for(int eventIdx = dwIndex; eventIdx < ClientList.size(); eventIdx++) //WSAWaitForMultipleEvents 때문에 for문 돌려줘야함.
		{
			DWORD dwSignalIdx = WSAWaitForMultipleEvents(1, &m_EventList[eventIdx], TRUE, 0, FALSE);
			if (dwIndex == WSA_WAIT_FAILED)
			{
				continue;
			}

			if (dwIndex == WSA_WAIT_TIMEOUT)
			{
				continue;
			}

			SocketNetwork::SocketEx* m_ClientList[64];
			SocketNetwork::SocketEx* Client = m_ClientList[eventIdx];
			WSANETWORKEVENTS networkEvent;
			int rst = WSAEnumNetworkEvents(Client->Socket, m_EventList[eventIdx], &networkEvent);

			if (rst == SOCKET_ERROR)
			{
				return false;
			}

			if (networkEvent.lNetworkEvents & FD_READ)
			{
				// networkEvent에 발생한 이벤트를 받아와서 FD_ACCEPT와 같으면 Accept를 처리하면 된다.
			}

			if (networkEvent.lNetworkEvents & FD_WRITE)
			{
				// networkEvent에 발생한 이벤트를 받아와서 FD_ACCEPT와 같으면 Accept를 처리하면 된다.
			}

			if (networkEvent.lNetworkEvents & FD_CLOSE)
			{
				// networkEvent에 발생한 이벤트를 받아와서 FD_ACCEPT와 같으면 Accept를 처리하면 된다.
			}
		}

		// 각 유저를 Accept 할 때 Event를 만들어 EventList에 넣어주고 EventSelect 해줘야 함.
		if (0) // Accept
		{
			HANDLE ClientEvent = WSACreateEvent(); // 통신에도 API처럼 이벤트가 있지만 수동 리셋 이벤트만 있다.
			m_EventList[ClientList.size()] = ClientEvent;
			WSAEventSelect(HostSocket.Socket, ClientEvent, FD_READ | FD_WRITE | FD_CLOSE); // 이벤트를 소켓에 바인딩 하여 사용 가능.
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