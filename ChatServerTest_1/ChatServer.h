#pragma once
#include "SocketNetwork.h"

#define WM_USER_NETWORK_MSG (WM_USER+0)

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
	virtual bool Open(HWND hWnd);

public:
	virtual bool Run() override;
	virtual bool AddClient(SocketNetwork::SocketEx* client) override;
};