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
	// 소켓 초기화, 윈도우에 문제 있지 않는 한 실패하는 경우는 거의 없음.
	// MAKEWORD(2, 2): 윈도우 소켓 2.2 버전
	if (WSAStartup(MAKEWORD(2, 2), &Wsa) != 0)
	{
		return;
	}

	// 소켓을 꼭 만들어야 사용 가능하다.
	// AF_INET: IP를 뜻함.
	// SOCKET sockTCP = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // SOCK_STREAM: TCP.
	// SOCKET sockUDP = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // SOCK_DGRAM: UDP
	
	if (Protocol == ProtocolType::TCP)
	{
		MainSocket = socket(AF_INET, SOCK_STREAM, 0); // TCP는 STREAM으로 고정이기 때문에 프로토콜에 0을 넣어줘도 된다.
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

	// 서버 바인딩.
	int rst = bind(MainSocket, (sockaddr*)&MainSockAddr, sizeof(MainSockAddr));
	if (rst == SOCKET_ERROR)
	{
		return false;
	}

	// 데이터 리딩 준비.
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
	// 만든 소켓 닫기.
	closesocket(MainSocket);

	// 소켓 클리어.
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
