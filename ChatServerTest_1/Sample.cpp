#include "Sample.h"

// 2022-09-06

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    Sample sampleWindow;
    sampleWindow.createWindow(hInstance, L"TestName", 1024, 768);
    sampleWindow.run();

    return 1;
}

bool Sample::run()
{
	MainServer = new SocketNetwork::SelectModelServer(hWnd);
	MainServer->Open(10000);
	MainServer->Run();

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); // 메세지 번역
			DispatchMessage(&msg); // 메세지 프로시져에 전달
		}
	}

	return true;
}

//bool Sample::initialize()
//{
//    return true;
//}
//
//bool Sample::frame()
//{
//    return true;
//}
//
//bool Sample::render()
//{
//    return true;
//}
//
//bool Sample::release()
//{
//    return true;
//}

LRESULT Sample::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		ListBoxHandle = CreateWindow(L"listbox", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER, 0, 0, 500, 600, hWnd, (HMENU)1000, hInstance, NULL);
		EditBoxHandle = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 600, 450, 25, hWnd, (HMENU)1001, hInstance, NULL);
		ButtonHandle = CreateWindow(L"button", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 450, 600, 50, 25, hWnd, (HMENU)1002, hInstance, NULL);
	}
	break;
	case WM_USER_NETWORK_MSG:
	{
		if (WSAGETSELECTERROR(lParam) != 0)
		{
			break;
		}
		DWORD dwSelect = WSAGETSELECTEVENT(lParam);
		switch (dwSelect)
		{
		case FD_CONNECT:
		{
			int a = 0;
		}break;
		case FD_READ:
		{
			SOCKET sock = wParam;
			std::string msg;
			if (MainServer->ReceiveFromClient(sock, msg))
			{
				MainServer->SendMsgToClientAll(msg, 255);
				std::wstring wMsg(msg.begin(), msg.end());
				SendMessage(ListBoxHandle, LB_ADDSTRING, 0, (LPARAM)wMsg.c_str());
			}
			int a = 0;
			
		}break;
		case FD_WRITE:
		{
			int at = 0;
		}break;
		case FD_CLOSE:
		{
			SOCKET sock = wParam;
			if (MainServer->CloseClient(sock))
			{

			}
		}break;
		case FD_ACCEPT:
		{
			MainServer->AcceptClient();
		}break;

		}
	} break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 1002:
		{
			WCHAR szBuffer[255] = L"";
			GetWindowText(EditBoxHandle, szBuffer, 255);
			std::string msg;
			for (int i = 0; i < 255; i++)
			{
				msg.push_back(szBuffer[i]);
			}
			MainServer->SendMsgToClientAll(msg, 255);
			SendMessage(ListBoxHandle, LB_ADDSTRING, 0, (LPARAM)szBuffer);
			//OutputDebugString(szBuffer);

		} break;
		}
	}
		
	case WM_SIZE:
	{
		//UINT width = LOWORD(lParam);
		//UINT height = HIWORD(wParam);
		GetClientRect(hWnd, &clientRect);
		resize();
	} break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
