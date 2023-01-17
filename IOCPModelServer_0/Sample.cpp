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
	initialize();

	bool isGameRun = true;
	while (isGameRun)
	{
		if (WindowUI::run() == true)
		{
			frame();
			render();
		}
		else
		{
			isGameRun = false;
		}
	}

	release();

	//MSG msg;
	//ZeroMemory(&msg, sizeof(MSG));
	//while (WM_QUIT != msg.message)
	//{
	//	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	//	{
	//		TranslateMessage(&msg); // 메세지 번역
	//		DispatchMessage(&msg); // 메세지 프로시져에 전달
	//	}
	//}

	return true;
}

void Sample::Print(std::string msg, ...)
{
	va_list arg;
		va_start(arg, msg);
		USES_CONVERSION;
		SendMessage(ListBoxHandle, LB_ADDSTRING, 0, (LPARAM)A2W(msg.c_str()));
	va_end(arg);
}

bool Sample::initialize()
{
	MainServer.Initialize();
	bool rst = MainServer.Open(10000);

	MainServer.ReceiveMsg = std::bind(&Sample::Print, this, std::placeholders::_1);

	return rst;
}

bool Sample::frame()
{
    return true;
}

bool Sample::render()
{
    return true;
}

bool Sample::release()
{
    return true;
}

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
				}
				break;

				case FD_READ:
				{
					SOCKET sock = wParam;
					std::string msg;
					if (MainServer->ReceiveFromClient(sock, msg))
					{
						MainServer->SendMsgToClientAll(msg, 255);
						Print(msg);
					}
					int a = 0;
				}
				break;

				case FD_WRITE:
				{
			
				}
				break;

				case FD_CLOSE:
				{
					SOCKET sock = wParam;
					if (MainServer->CloseClient(sock))
					{

					}
				}
				break;

				case FD_ACCEPT:
				{
					MainServer->AcceptClient();
				}
				break;

			}
		} 
		break;

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case 1002:
				{
					WCHAR szBuffer[255] = L"";
					GetWindowText(EditBoxHandle, szBuffer, 255);
					USES_CONVERSION;
					std::string msg = W2A(szBuffer);
					if (msg.empty())
					{
						break;
					}

					MainServer->SendMsgToClientAll(msg, 255);
					Print(msg);
					SetWindowText(EditBoxHandle, L"");

				} 
				break;
			}
		}
		
		case WM_SIZE:
		{
			//UINT width = LOWORD(lParam);
			//UINT height = HIWORD(wParam);
			GetClientRect(hWnd, &clientRect);
			resize();
		} 
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
