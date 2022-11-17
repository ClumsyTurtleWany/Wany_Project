#include "WindowUI.hpp"

WindowUI* g_pWindow = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd,	UINT message, WPARAM wParam, LPARAM lParam)
{
	_ASSERT(g_pWindow);
	return g_pWindow->MsgProc(hWnd, message, wParam, lParam);
}

LRESULT WindowUI::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		/*case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			EndPaint(hWnd, &ps);
		}
		break;*/
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

WindowUI::WindowUI()
{
	g_pWindow = this;
}

BOOL WindowUI::initInstance(const WCHAR* _title, UINT _width, UINT _height)
{
	// Wany
	// �ü���� �����(RegisterWindow) �����츦 �����Ѵ�.
	DWORD csStyle = WS_OVERLAPPEDWINDOW;
	RECT rc = { 0, 0, static_cast<LONG>(_width), static_cast<LONG>(_height) };
	AdjustWindowRect(&rc, csStyle, FALSE);

	int clientWidth = rc.right - rc.left;
	int clientHeight = rc.bottom - rc.top;
	int monitorWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int monitorHeight = GetSystemMetrics(SM_CYFULLSCREEN);
	int x = static_cast<UINT>((monitorWidth - clientWidth) * 0.5f);
	int y = static_cast<UINT>((monitorHeight - clientHeight) * 0.5f);

	hWnd = CreateWindowExW(0, L"WindowUI", _title, WS_OVERLAPPEDWINDOW, x, y, clientWidth, clientHeight, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		OutputDebugString(L"WanyCore::WindowUI::Failed Create Window.\n");
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOW);
	//UpdateWindow(hWnd);

	GetClientRect(hWnd, &clientRect);

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
	wcex.lpszClassName = L"WindowUI"; // ������ ���� ����... hWnd = CreateWindow �� ���� �̸��� ���ƾ� ��.
	//wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

bool WindowUI::createWindow(HINSTANCE _hInstance, const WCHAR* _title, UINT _width, UINT _height)
{
	hInstance = _hInstance;
	WORD rst = MyRegisterClass();
	if (!initInstance(_title, _width, _height))
	{
		OutputDebugString(L"WanyCore::WindowUI::Failed initInstance.\n");
		return false;
	}
	return true;
}

RECT WindowUI::getClientRect()
{
	return clientRect;
}

float WindowUI::getClientWidth()
{
	return static_cast<float>(clientRect.right - clientRect.left);
}

float WindowUI::getClientHeight()
{
	return static_cast<float>(clientRect.bottom - clientRect.top);
}

Vector2f WindowUI::getClientCenterPos()
{
	Vector2f pos;
	pos.x = getClientWidth() * 0.5f;
	pos.y = getClientHeight() * 0.5f;
	return pos;
}

void WindowUI::enableResize()
{
	SetWindowLongW(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
	UpdateWindow(hWnd);
	ShowWindow(hWnd, SW_SHOW);
}

void WindowUI::disableResize()
{
	LONG newStyle = GetWindowLong(hWnd, GWL_STYLE);
	newStyle &= ~(WS_THICKFRAME);
	newStyle &= ~(WS_MINIMIZEBOX);
	newStyle &= ~(WS_MAXIMIZEBOX);
	SetWindowLongW(hWnd, GWL_STYLE, newStyle);
	
	UpdateWindow(hWnd);
	ShowWindow(hWnd, SW_SHOW);
}

void WindowUI::setWindowHandle(HWND _hWnd)
{
	hWnd = _hWnd;
	GetClientRect(hWnd, &clientRect);
}

bool WindowUI::run()
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
#ifdef CoreMode
		else
		{
			return true;
		}
#endif
	}

	return false;
}

bool WindowUI::resize()
{
	return true;
}

bool WindowUI::enableFullScreen()
{
	return true;
}

bool WindowUI::disableFullScreen()
{
	return true;
}

