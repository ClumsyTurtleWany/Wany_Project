#include "SocketNetwork.h"

using namespace SocketNetwork;

Host::Host(int port, ProtocolType protocol)
{
	Port = port;
	Protocol = protocol;
}

Host::~Host()
{
}

bool Host::initialize()
{
	// ���� �ʱ�ȭ, �����쿡 ���� ���� �ʴ� �� �����ϴ� ���� ���� ����.
	// MAKEWORD(2, 2): ������ ���� 2.2 ����
	if (WSAStartup(MAKEWORD(2, 2), &Wsa) != 0)
	{
		return;
	}

	// ������ �� ������ ��� �����ϴ�.
	// AF_INET: IP�� ����.
	// SOCKET sockTCP = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // SOCK_STREAM: TCP.
	// SOCKET sockUDP = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // SOCK_DGRAM: UDP
	
	if (Protocol == ProtocolType::TCP)
	{
		MainSocket = socket(AF_INET, SOCK_STREAM, 0); // TCP�� STREAM���� �����̱� ������ �������ݿ� 0�� �־��൵ �ȴ�.
	}
	else if (Protocol == ProtocolType::UDP)
	{
		MainSocket = socket(AF_INET, SOCK_DGRAM, 0);
	}
	else
	{
		return false;
	}
	
	MainSockAddr.sin_family = AF_INET;
	MainSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	MainSockAddr.sin_port = htons(Port);

	// ���� ���ε�.
	int rst = bind(MainSocket, (sockaddr*)&MainSockAddr, sizeof(MainSockAddr));
	if (rst == SOCKET_ERROR)
	{
		return false;
	}

	// ������ ���� �غ�.
	rst = listen(MainSocket, SOMAXCONN);
	if (rst == SOCKET_ERROR)
	{
		return false;
	}

	RunEventHandle = CreateEvent(NULL, FALSE, FALSE, TEXT("run"));
	AcceptThreadHandle = CreateThread(NULL, 0, AcceptThread, this, 0, 0);

	return true;
}

bool Host::release()
{
	// ���� ���� �ݱ�.
	closesocket(MainSocket);

	// ���� Ŭ����.
	WSACleanup();

	return false;
}

bool SocketNetwork::Host::addClient(SOCKET socket, SOCKADDR_IN addr)
{
	ClientInfo* newClient = new ClientInfo;
	newClient->Socket = socket;
	newClient->Addr = addr;

	ClientList.push_back(newClient);

	CreateThread(NULL, 0, ReceiveThread, , 0, 0);

	return false;
}

bool Host::run()
{
	SetEvent(RunEventHandle);
	return false;
}

bool Host::pause()
{
	ResetEvent(RunEventHandle);
	return false;
}

bool Host::stop()
{
	return false;
}

DWORD __stdcall SocketNetwork::Host::AcceptThread(LPVOID lpParam)
{
	Host* host = (Host*)lpParam;
	if (host == nullptr)
	{
		return -1;
	}

	while (1)
	{
		DWORD dw = WaitForSingleObject(host->ExitEventHandle, 1);
		if (dw == WAIT_OBJECT_0)
		{
			break;
		}

		WaitForSingleObject(host->RunEventHandle, INFINITE);

		SOCKADDR_IN ClientAddr;
		int length = sizeof(ClientAddr);
		SOCKET ClientSocket = accept(host->MainSocket, (sockaddr*)&ClientAddr, &length);
		if (ClientSocket == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				continue;
			}
		}

		host->addClient(ClientSocket, ClientAddr);
	}

	return 0;
}

DWORD __stdcall SocketNetwork::Host::ReceiveThread(LPVOID lpParam)
{
	return 0;
}
