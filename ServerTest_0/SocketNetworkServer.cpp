#include "SocketNetwork.h"

SocketNetwork::Server::Server()
{
	Initialize();
}

SocketNetwork::Server::~Server()
{
	Release();
}

bool SocketNetwork::Server::Initialize()
{
	return SocketNetwork::StartUp();
}

bool SocketNetwork::Server::Release()
{
	for (auto& it : HostList)
	{
		SocketEx* Socket = it.second;
		if (Socket == nullptr)
		{
			continue;
		}

		SocketNetwork::CloseSocket(*Socket);
		delete Socket;
		Socket = nullptr;
	}

	HostList.clear();

	for (auto& it : ClientList)
	{
		SocketEx* Socket = it.second;
		if (Socket == nullptr)
		{
			continue;
		}

		SocketNetwork::CloseSocket(*Socket);
		delete Socket;
		Socket = nullptr;
	}

	ClientList.clear();

	return SocketNetwork::CleanUp();
}

bool SocketNetwork::Server::Open(int port, ProtocolType protocol)
{
	if (!SocketNetwork::OpenSocket(HostSocket, protocol))
	{
		return false;
	}

	if (!SocketNetwork::Bind(HostSocket, port))
	{
		return false;
	}

	if (!SocketNetwork::Listen(HostSocket))
	{
		return false;
	}

	isOpen = true;
	return isOpen;
}

bool SocketNetwork::Server::Close()
{
	if (!isOpen)
	{
		return false;
	}

	SetEvent(ExitEventHandle);

	SocketNetwork::CloseSocket(HostSocket);

	return true;
}


bool SocketNetwork::Server::Connect(std::string name, std::string ip, int port)
{
	SocketEx* newSocket = new SocketEx;
	if (!SocketNetwork::OpenSocket(*newSocket))
	{
		delete newSocket;
		newSocket = nullptr;
		return false;
	}

	if (!SocketNetwork::Connect(*newSocket, ip, port))
	{
		delete newSocket;
		newSocket = nullptr;
		return false;
	}

	HostList.insert(std::make_pair(name, newSocket));

	return true;
}

bool SocketNetwork::Server::Run()
{
	if (!isOpen)
	{
		return false;
	}

	ExitEventHandle = CreateEvent(NULL, FALSE, FALSE, TEXT("Exit"));

	return RunAcceptThread();
}

bool SocketNetwork::Server::SendMsgToHost(std::string name, std::string& msg)
{
	if (msg.empty())
	{
		return false;
	}

	auto it = HostList.find(name);
	if (it == HostList.end())
	{
		return false;
	}

	return SocketNetwork::Send(*it->second, msg);
}

bool SocketNetwork::Server::SendMsgToClient(std::string name, std::string& msg)
{
	if (!isOpen)
	{
		return false;
	}

	if (msg.empty())
	{
		return false;
	}

	auto it = ClientList.find(name);
	if (it == ClientList.end())
	{
		return false;
	}

	return SocketNetwork::Send(*it->second, msg);
}

bool SocketNetwork::Server::SendMsgToHostAll(std::string& msg)
{
	if (msg.empty())
	{
		return false;
	}

	for (auto& it : HostList)
	{
		SocketEx* Socket = it.second;
		if (Socket == nullptr)
		{
			continue;
		}

		SocketNetwork::Send(*Socket, msg);
	}

	return true;
}

bool SocketNetwork::Server::SendMsgToClientAll(std::string& msg)
{
	if (!isOpen)
	{
		return false;
	}

	if (msg.empty())
	{
		return false;
	}

	for (auto& it : ClientList)
	{
		SocketEx* Socket = it.second;
		if (Socket == nullptr)
		{
			continue;
		}

		SocketNetwork::Send(*Socket, msg);
	}

	return true;
}

bool SocketNetwork::Server::SendMsgToAll(std::string& msg)
{
	if (msg.empty())
	{
		return false;
	}

	bool isSucessed = SendMsgToHostAll(msg);

	if (isOpen)
	{
		isSucessed &= SendMsgToClientAll(msg);
	}

	return isSucessed;
}

bool SocketNetwork::Server::RunAcceptThread()
{
	if (AcceptThreadHandle != NULL)
	{
		return false;
	}

	AcceptThreadHandle = CreateThread(NULL, 0, AcceptThread, this, 0, 0);

	return true;
}

bool SocketNetwork::Server::RunClientReceiveThread(SocketEx* client)
{
	ReceiveThreadInfo* ThreadInfo = new ReceiveThreadInfo;
	ThreadInfo->HostServer = this;
	ThreadInfo->Client = client;

	CreateThread(NULL, 0, ReceiveThread, ThreadInfo, 0, 0);

	return true;
}

bool SocketNetwork::Server::AddClient(SocketEx* client)
{
	if (client == nullptr)
	{
		return false;
	}

	client->IP = inet_ntoa(client->Addr.sin_addr);
	client->Port = ntohs(client->Addr.sin_port);

	std::string name = client->IP + ":" + std::to_string(client->Port);
	ClientList.insert(std::make_pair(name, client));

	return RunClientReceiveThread(client);
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

		SocketEx* newClient = SocketNetwork::Accept(HostServer->HostSocket);
		if(newClient == nullptr)
		{
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

	while (Client != nullptr)
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

			
		}
	}

	return 0;
}