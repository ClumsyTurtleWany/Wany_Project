#pragma once
#include "SocketNetwork.h"

class ChatServer : public SocketNetwork::Server
{
public:
	typedef struct ChatInfo
	{
		ChatServer* HostServer;
		SocketNetwork::SocketEx* Client;
	};

public:
	std::vector<std::string> MsgLog;
	HWND MsgBoxHandle;

public:
	virtual bool RunClientReceiveThread(SocketNetwork::SocketEx* client) override;

public:
	static DWORD WINAPI ReceiveThread(LPVOID lpParam);
};