#pragma once
#include "SocketNetwork.h"

#define NETWORK_MSG (int)1000
#define WM_USER_NETWORK_MSG (WM_USER + NETWORK_MSG)

namespace SocketNetwork
{
	class SelectModelServer : public Server
	{
	private:
		HWND m_hWnd;

	public:
		SelectModelServer(HWND hWnd);
		virtual ~SelectModelServer();

	public:
		virtual bool Run();
		virtual bool AddClient(SocketEx* client);

	public:
		virtual bool AcceptClient();
		virtual bool CloseClient(SOCKET sock);
		virtual bool ReceiveFromClient(SOCKET sock, std::string& msg);
	};
}