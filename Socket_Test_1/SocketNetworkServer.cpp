#include "SocketNetwork.h"

SocketNetwork::Server::Server()
{
}

SocketNetwork::Server::~Server()
{
}

bool SocketNetwork::Server::Open(int port, ProtocolType protocol)
{
	if (!SocketNetwork::OpenSocket(SelfHost, protocol))
	{
		return false;
	}

	if (!SocketNetwork::Bind(SelfHost, port))
	{
		return false;
	}

	isOpen = true;
	return isOpen;
}

bool SocketNetwork::Server::Connect(std::string ip, int port)
{
	SocketEx* newSocket = new SocketEx;
	if (!SocketNetwork::Connect(*newSocket, ip, port))
	{
		delete newSocket;
		newSocket = nullptr;
		return false;
	}

	HostList.push_back(newSocket);

	return true;
}

bool SocketNetwork::Server::Run()
{
	if (!isOpen)
	{
		return false;
	}

	if (AcceptThreadHandle == NULL)
	{
		ExitEventHandle = CreateEvent(NULL, FALSE, FALSE, TEXT("Exit"));
		AcceptThreadHandle = CreateThread(NULL, 0, AcceptThread, this, 0, 0);
	}

	return true;
}

bool SocketNetwork::Server::Send(std::string& msg)
{
	if (msg.empty())
	{
		return false;
	}

	SendToHost(msg);
	SendToClient(msg);

	return true;
}

bool SocketNetwork::Server::Close()
{
	for (auto& it : HostList)
	{
		if (it == nullptr)
		{
			continue;
		}

		SocketNetwork::Close(*it);
		delete it;
		it = nullptr;
	}

	HostList.clear();

	for (auto& it : ClientList)
	{
		if (it == nullptr)
		{
			continue;
		}

		SocketNetwork::Close(*it);
		delete it;
		it = nullptr;
	}

	ClientList.clear();

	SocketNetwork::Close(SelfHost);

	return false;
}

bool SocketNetwork::Server::AddClient(SocketEx* client)
{
	if (client == nullptr)
	{
		return false;
	}

	ClientList.push_back(client);
	ReceiveThreadInfo* ThreadInfo = new ReceiveThreadInfo;
	ThreadInfo->HostServer = this;
	ThreadInfo->Client = client;

	CreateThread(NULL, 0, ReceiveThread, ThreadInfo, 0, 0);
}

bool SocketNetwork::Server::SendToHost(std::string& msg)
{
	for (auto& it : HostList)
	{
		if (it == nullptr)
		{
			continue;
		}

		SocketNetwork::Send(*it, msg);
	}
	return true;
}

bool SocketNetwork::Server::SendToClient(std::string& msg)
{
	for (auto& it : ClientList)
	{
		if (it == nullptr)
		{
			continue;
		}

		SocketNetwork::Send(*it, msg);
	}
	return true;
}

DWORD __stdcall SocketNetwork::Server::AcceptThread(LPVOID lpParam)
{
	Server* HostServer = (Server*)lpParam;
	if (HostServer == nullptr)
	{
		return -1;
	}

	while (1)
	{
		DWORD dw = WaitForSingleObject(HostServer->ExitEventHandle, 1);
		if (dw == WAIT_OBJECT_0)
		{
			break;
		}

		SocketEx* newClient = new SocketEx;
		if (!SocketNetwork::Accept(HostServer->SelfHost, *newClient))
		{
			delete newClient;
			newClient = nullptr;
			continue;
		}

		HostServer->AddClient(newClient);
	}

	return 0;
}

DWORD __stdcall SocketNetwork::Server::ReceiveThread(LPVOID lpParam)
{
	ReceiveThreadInfo* ThreadInfo = (ReceiveThreadInfo*)lpParam;
	if (ThreadInfo == nullptr)
	{
		return -1;
	}

	Server* HostServer = ThreadInfo->HostServer;
	SocketEx* Client = ThreadInfo->Client;

	while (1)
	{
		DWORD dw = WaitForSingleObject(HostServer->ExitEventHandle, 1);
		if (dw == WAIT_OBJECT_0)
		{
			break;
		}

		std::string ReceiveMsg;
		if (SocketNetwork::Receive(*Client, ReceiveMsg))
		{
			if (ReceiveMsg.empty())
			{
				return 0;
			}

			std::string SendMsg = Client->IP + " Send Msg: ";
			SendMsg.append(ReceiveMsg);
			HostServer->Send(SendMsg);
		}
	}

	return 0;
}