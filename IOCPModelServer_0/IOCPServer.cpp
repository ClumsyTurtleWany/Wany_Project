#include "IOCPServer.h"

SocketNetwork::IOCPServer::IOCPServer()
{
}

SocketNetwork::IOCPServer::~IOCPServer()
{
}

bool SocketNetwork::IOCPServer::Initialize()
{
	IOCPHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	for (int idx = 0; idx < MAX_WORK_THREAD; idx++)
	{
		WorkThreadHandle[idx] = CreateThread(NULL, 0, WorkThread, this, 0, &WorkThreadID[idx]);
	}

	return SocketNetwork::Server::Initialize();
}

bool SocketNetwork::IOCPServer::Release()
{
	CloseHandle(IOCPHandle);
	for (int idx = 0; idx < MAX_WORK_THREAD; idx++)
	{
		CloseHandle(WorkThreadHandle[idx]);
	}
	
	return SocketNetwork::Server::Release();
}

bool SocketNetwork::IOCPServer::SendMsg(SocketEx* target, std::string msg)
{
	// WSABUF랑 OVERLAPPED는 패킷이 끝나기 전에 사라지면 안되기 때문에 클라이언트의 멤버 변수로 이관하거나 할 필요가 있다.
	WSABUF wsaBuffer; 
	wsaBuffer.buf = (char*)msg.c_str();
	wsaBuffer.len = msg.size();

	OVERLAPPED sendOV;
	ZeroMemory(&sendOV, sizeof(OVERLAPPED));

	DWORD dwSendBytes;
	int rst = WSASend(target->Socket, &wsaBuffer, 1, &dwSendBytes, 0, &sendOV, NULL);
	if (rst == SOCKET_ERROR)
	{
		if (GetLastError() == EWOULDBLOCK)
		{
			return false;
		}
	}

	return true;
}

bool SocketNetwork::IOCPServer::Run()
{
	if(!SocketNetwork::Server::Run())
	{
		return false;
	}

	

	return true;
}

bool SocketNetwork::IOCPServer::AddClient(SocketEx* client)
{
	if (client == nullptr)
	{
		return false;
	}

	client->IP = inet_ntoa(client->Addr.sin_addr);
	client->Port = ntohs(client->Addr.sin_port);

	std::string name = client->IP + ":" + std::to_string(client->Port);
	ClientList.insert(std::make_pair(name, client));

	::CreateIoCompletionPort((HANDLE)client->Socket, IOCPHandle, (ULONG_PTR)client, 0);

	return true;
}

DWORD __stdcall SocketNetwork::IOCPServer::WorkThread(LPVOID lpParam)
{
	IOCPServer* HostServer = (IOCPServer*)lpParam;

	DWORD dwTransfer;
	ULONG_PTR key;
	OVERLAPPED* pOV;
	while (1)
	{
		DWORD dw = WaitForSingleObject(HostServer->ExitEventHandle, 0);
		if (dw == WAIT_OBJECT_0)
		{
			break;
		}

		BOOL rst = ::GetQueuedCompletionStatus(HostServer->IOCPHandle, &dwTransfer, &key, &pOV, INFINITE);
		if (rst == TRUE)
		{
			SocketEx* Client = (SocketEx*)key;
		}
		else
		{
			if (GetLastError() == ERROR_HANDLE_EOF)
			{
				break;
			}
		}
	
	}




	return 0;
}
