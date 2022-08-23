#pragma once
#include <windows.h>

class WindowUI
{
public:
	HINSTANCE	hInstance;
	HWND		hWnd;

public:
	BOOL initInstance(const WCHAR* _title, UINT _width, UINT _height);
	ATOM MyRegisterClass();
	bool createWindow(HINSTANCE _hInstance, const WCHAR* _title, UINT _width, UINT _height);
	bool run();

public:
	static LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
	
};

BOOL WindowUI::initInstance(const WCHAR* _title, UINT _width, UINT _height)
{
   // Wany
   // �ü���� �����(RegisterWindow) �����츦 �����Ѵ�.
	hWnd = CreateWindowExW(0, L"Test", _title, WS_OVERLAPPEDWINDOW, 0, 0, _width, _height, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOW);
	//UpdateWindow(hWnd);

	return TRUE;
}

ATOM WindowUI::MyRegisterClass()
{
	// Wany
	// �ü������ �ش� �����츦 ���� ��� ��û�ϴ� �Լ�.
	// WND: window, Class, EX: extension, W: wide(unicode)
	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	// Wany
	// lp: pointer, fn: function, Wnd: window, Proc: procedure, �԰� ����������. ���� �߿�
	// ������ �޼����� ���� �Լ��� ����.
	wcex.lpfnWndProc = WndProc; // ���� �Լ��� Static�� �Է� ����.
	//wcex.cbClsExtra = 0;
	//wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	//wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSTUDY0));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSTUDY0);
	wcex.lpszClassName = L"Test"; // ������ ���� �����ϴ���...
	//wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

bool WindowUI::createWindow(HINSTANCE _hInstance, const WCHAR* _title, UINT _width, UINT _height)
{
	hInstance = _hInstance;
	WORD rst = MyRegisterClass();
	if (!initInstance(_title, _width, _height))
	{
		return false;
	}
	return true;
}

bool WindowUI::run()
{
	if (initialize())
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg); // �޼��� ����
				DispatchMessage(&msg); // �޼��� ���ν����� ����
			}
			else
			{
				frame();
				render();
			}
		}
		release();

		return true;
	}
	else
	{
		return false;
	}
}

LRESULT WindowUI::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	//case WM_COMMAND:
	//{
	//	int wmId = LOWORD(wParam);
	//	// �޴� ������ ���� �м��մϴ�:
	//	switch (wmId)
	//	{
	//	case IDM_ABOUT:
	//		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
	//		break;
	//	case IDM_EXIT:
	//		DestroyWindow(hWnd);
	//		break;
	//	default:
	//		// Wany
	//		// DefWindowProc: �޼��� ���� ó�� �Ұ�, ��� ó�� �� �ִ� �Լ�.
	//		return DefWindowProc(hWnd, message, wParam, lParam);
	//	}
	//}
	//break;
	//case WM_PAINT:
	//{
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(hWnd, &ps);
	//	// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
	//	EndPaint(hWnd, &ps);
	//}
	//break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

bool WindowUI::initialize()
{
	return true;
}

bool WindowUI::frame()
{
	return true;
}

bool WindowUI::render()
{
	return true;
}

bool WindowUI::release()
{
	return true;
}




class TestUI : public WindowUI
{
public:
	bool initialize() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};

bool TestUI::initialize()
{
	return true;
}
bool TestUI::frame()
{
	return true;
}
bool TestUI::render()
{
	return true;
}
bool TestUI::release()
{
	return true;
}