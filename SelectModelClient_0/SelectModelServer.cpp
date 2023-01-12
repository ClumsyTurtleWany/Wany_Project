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

	if (0) // �� ������ ���� ��.
	{
		HANDLE ListenEvent = WSACreateEvent(); // ��ſ��� APIó�� �̺�Ʈ�� ������ ���� ���� �̺�Ʈ�� �ִ�.
		HANDLE m_EventList[64];
		m_EventList[0] = ListenEvent; // 0���� �־��� ������ WSAWaitForMultipleEvents�� ��ȯ���� ���� ���� �ε����� ��ȯ�ϱ� ������
		WSAEventSelect(HostSocket.Socket, ListenEvent, FD_ACCEPT); // �̺�Ʈ�� ���Ͽ� ���ε� �Ͽ� ��� ����.
		DWORD dwIndex = WSAWaitForMultipleEvents(ClientList.size() + 1, m_EventList, FALSE, 0, FALSE); // �̺�Ʈ�� �߻��� �̺�Ʈ �ε��� ��ȯ �� ��. ���� �̺�Ʈ�� ���ÿ� �߻��ϸ� ���� ���� �ε������� ��ȯ �ȴ�.
		if (dwIndex == WSA_WAIT_FAILED)
		{
			return false;
		}

		if (dwIndex == WSA_WAIT_TIMEOUT)
		{
			return false;
		}

		dwIndex = dwIndex - WSA_WAIT_EVENT_0; // �̺�Ʈ�� ���� ��ġ�� ����.
		if (dwIndex == 0) // m_EventList[0]�� Host ���� + FD_ACCEPT ���ε� �� ������ 0���� ��ȯ�Ǹ� ȣ��Ʈ���� �� �� ó��
		{
			// Event List�� Accept�� ���ε� �����Ƿ� Accept ó��.
			WSANETWORKEVENTS networkEvent;
			int rst = WSAEnumNetworkEvents(HostSocket.Socket, m_EventList[dwIndex], &networkEvent);
			if (rst == SOCKET_ERROR)
			{
				return false;
			}

			if (networkEvent.lNetworkEvents & FD_ACCEPT)
			{
				// networkEvent�� �߻��� �̺�Ʈ�� �޾ƿͼ� FD_ACCEPT�� ������ Accept�� ó���ϸ� �ȴ�.
			}
		}

		for(int eventIdx = dwIndex; eventIdx < ClientList.size(); eventIdx++) //WSAWaitForMultipleEvents ������ for�� ���������.
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
				// networkEvent�� �߻��� �̺�Ʈ�� �޾ƿͼ� FD_ACCEPT�� ������ Accept�� ó���ϸ� �ȴ�.
			}

			if (networkEvent.lNetworkEvents & FD_WRITE)
			{
				// networkEvent�� �߻��� �̺�Ʈ�� �޾ƿͼ� FD_ACCEPT�� ������ Accept�� ó���ϸ� �ȴ�.
			}

			if (networkEvent.lNetworkEvents & FD_CLOSE)
			{
				// networkEvent�� �߻��� �̺�Ʈ�� �޾ƿͼ� FD_ACCEPT�� ������ Accept�� ó���ϸ� �ȴ�.
			}
		}

		// �� ������ Accept �� �� Event�� ����� EventList�� �־��ְ� EventSelect ����� ��.
		if (0) // Accept
		{
			HANDLE ClientEvent = WSACreateEvent(); // ��ſ��� APIó�� �̺�Ʈ�� ������ ���� ���� �̺�Ʈ�� �ִ�.
			m_EventList[ClientList.size()] = ClientEvent;
			WSAEventSelect(HostSocket.Socket, ClientEvent, FD_READ | FD_WRITE | FD_CLOSE); // �̺�Ʈ�� ���Ͽ� ���ε� �Ͽ� ��� ����.
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