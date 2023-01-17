#pragma once
#include "SocketNetwork.h"
#include <functional>

#define NETWORK_MSG (int)1000
#define WM_USER_NETWORK_MSG (WM_USER + NETWORK_MSG)
#define MAX_WORK_THREAD (int)4

namespace SocketNetwork
{
	class IOCPServer : public Server
	{
	public:
		typedef struct IOCPSession
		{

		};

	protected:
		HANDLE	IOCPHandle;
		HANDLE	WorkThreadHandle[MAX_WORK_THREAD];
		DWORD	WorkThreadID[MAX_WORK_THREAD];

	public:
		using CallFunction = std::function<void(std::string msg)>;

	public:
		CallFunction ReceiveMsg;

	public:
		IOCPServer();
		virtual ~IOCPServer();

	public:
		virtual bool Initialize() override;
		virtual bool Release() override;
		virtual bool AddClient(SocketEx* client) override;

	public:
		virtual bool SendMsg(SocketEx* target, std::string msg);
		virtual bool Run();

	public:
		static DWORD WINAPI WorkThread(LPVOID lpParam);
	};
}