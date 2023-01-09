#include "ChatServer.h"

bool ChatServer::RunClientReceiveThread(SocketNetwork::SocketEx* client)
{
	ChatInfo* newChatInfo = new ChatInfo;
	newChatInfo->HostServer = this;
	newChatInfo->Client = client;

	CreateThread(NULL, 0, ReceiveThread, newChatInfo, 0, 0);

	return false;
}

DWORD __stdcall ChatServer::ReceiveThread(LPVOID lpParam)
{
	ChatInfo* Info = (ChatInfo*)lpParam;
	if (Info == nullptr)
	{
		return -1;
	}

	ChatServer* HostServer = Info->HostServer;
	SocketNetwork::SocketEx* Client = Info->Client;
	
	while (Client != nullptr)
	{
		std::string ReceivedMsg;
		int length = 256;
		if (SocketNetwork::Receive(*Client, ReceivedMsg, 256))
		{
			std::string NewMsg = Client->IP + ":" + std::to_string(Client->Port) + " - ";
			NewMsg.append(ReceivedMsg);
			HostServer->MsgLog.push_back(NewMsg);
			WCHAR WMsg[255];
			ZeroMemory(WMsg, sizeof(WCHAR) * 255);
			for (int i = 0; i < NewMsg.size(); i++)
			{
				if (i >= 255)
				{
					break;
				}

				WMsg[i] = NewMsg.at(i);
			}
			SendMessage(HostServer->MsgBoxHandle, LB_ADDSTRING, 0, (LPARAM)WMsg);
			HostServer->SendMsgToClientAll(NewMsg, NewMsg.size());
		}
		else
		{
			delete Client;
			Client = nullptr;
		}
	}

	return 0;
}
