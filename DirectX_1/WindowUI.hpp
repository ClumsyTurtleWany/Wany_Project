#pragma once
#include <windows.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

class WindowUI
{
public:
	HINSTANCE	hInstance;
	HWND		hWnd;

	RECT clientRect;
	
public:
	BOOL initInstance(const WCHAR* _title, UINT _width, UINT _height);
	ATOM MyRegisterClass();
	bool createWindow(HINSTANCE _hInstance, const WCHAR* _title, UINT _width, UINT _height);

public:
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
	DWORD csStyle = WS_OVERLAPPEDWINDOW;
	RECT rc = {0, 0, _width, _height };
	AdjustWindowRect(&rc, csStyle, FALSE);
	
	UINT clientWidth = rc.right - rc.left;
	UINT clientHeight = rc.bottom - rc.top;
	UINT monitorWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	UINT monitorHeight = GetSystemMetrics(SM_CYFULLSCREEN);
	UINT x = (monitorWidth - clientWidth) * 0.5f;
	UINT y = (monitorHeight - clientHeight) * 0.5f;

	hWnd = CreateWindowExW(0, L"WindowUI", _title, WS_OVERLAPPEDWINDOW, x, y, clientWidth, clientHeight, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
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
	/*case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		
		EndPaint(hWnd, &ps);
	}
	break;*/
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
	// �������̽� -> �ϵ���� ���� ���� -> ȹ��
	ID3D11Device*			m_pd3dDevice = nullptr; // ����̽� ��ġ == ����̽� ��ü
	ID3D11DeviceContext*	m_pImmediateContext = nullptr;

	IDXGIFactory*			m_pGIFactory = nullptr; 
	IDXGISwapChain*			m_pSwapChain = nullptr;

	ID3D11RenderTargetView* m_pRTV = nullptr;

public:
	bool initialize() override;
	bool frame() override;
	bool render() override;
	bool release() override;

public:
	// 1) ����̽� ����
	HRESULT createDevice();
	// 2) ���丮 ����
	HRESULT createFactory();
	// 3) ����ü�� ����
	HRESULT createSwapChain();
	// 4) ���� Ÿ�ٺ� ����
	HRESULT createRenderTargetView();
	// 5) �� ��Ʈ ����
	void createViewPort();
};

bool TestUI::initialize()
{
	//////////////////////////////////////////////////////////////////////
	// 1) ����̽� ����
	//////////////////////////////////////////////////////////////////////

	if (FAILED(createDevice())) // 0�� �������� �� �־ SUCCEED FAILED�θ� ����� ��.
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////
	// 2) ���丮 ����
	//////////////////////////////////////////////////////////////////////
	
	if (FAILED(createFactory()))
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////
	// 3) ����ü�� ����
	//////////////////////////////////////////////////////////////////////
	
	if (FAILED(createSwapChain()))
	{
		return false;
	}


	//////////////////////////////////////////////////////////////////////
	// 4) ���� Ÿ�ٺ� ����
	//////////////////////////////////////////////////////////////////////
	
	if (FAILED(createRenderTargetView()))
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////
	// 5) �� ��Ʈ ����
	//////////////////////////////////////////////////////////////////////
	createViewPort();

	return true;
}
bool TestUI::frame()
{
	return true;
}
bool TestUI::render()
{
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL); // m_pRTV �� �Ѹ���.
	float color[4] = { 1.0f, 0, 0, 1.0f }; // R, G, B, A �� 0 ~ 1.0���� �� 1.0 == 255
	m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);
	m_pSwapChain->Present(0, 0); // 0�� ���۸� �Ѹ���.
	return true;
}
bool TestUI::release()
{
	if (m_pd3dDevice != nullptr)
	{
		m_pd3dDevice->Release();
	}

	if (m_pImmediateContext != nullptr)
	{
		m_pImmediateContext->Release();
	}

	if (m_pGIFactory != nullptr)
	{
		m_pGIFactory->Release();
	}

	if (m_pSwapChain != nullptr)
	{
		m_pSwapChain->Release();
	}

	if (m_pRTV != nullptr)
	{
		m_pRTV->Release();
	}
	return true;
}


// 1) ����̽� ����
HRESULT TestUI::createDevice()
{
	//////////////////////////////////////////////////////////////////////
	// 1) ����̽� ����
	//////////////////////////////////////////////////////////////////////
	//
	// HRESULT rst; // Dx�� ��� ��ȯ���� HRESULT ���
	// D3D_FEATURE_LEVEL* pFeatureLevel = nullptr; // �ȹ޾Ƶ� ��.
	// IDXGIAdapter* pAdapter = nullptr; // �׷��� ī��, nullptr�� ������ ���� ��� ���� �׷��� ī�� ��� �ϰڴ�
	// D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE; // �⺻�� D3D_DRIVER_TYPE_HARDWARE (GPU ó��)�� ���µ� �׷��� ī�尡 ������ ���� �ʰų� ����� �������� ������, Software(CPU ó��) ���� ���
	// HMODULE Software = NULL; // DirverType�� ���������� CPU ó���� ���� ��. NULL�� ��� ����.
	// UINT Flags = 0;
	// D3D_FEATURE_LEVEL pFeatureLevels[] = { /*D3D_FEATURE_LEVEL_12_0,*/ D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 }; // 12�� ����ϵ� ���� �ȵǸ� 11, 10 ������
	// UINT FeatureLevels = 2; // pFeatureLevels ���� ����
	// UINT SDKVersion = D3D11_SDK_VERSION; // ������ �ֽ����� ���� ��
	// ID3D11Device** ppDevice;
	// rst = D3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, &m_pd3dDevice, pFeatureLevel, &m_pImmediateContext); // ����̽� ����

	// ��� ����
	//HRESULT rst; // Dx�� ��� ��ȯ���� HRESULT ���
	D3D_FEATURE_LEVEL* pFeatureLevel = nullptr;
	D3D_FEATURE_LEVEL pFeatureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	ID3D11Device** ppDevice;
	//rst = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, pFeatureLevels, 1, D3D11_SDK_VERSION, &m_pd3dDevice, pFeatureLevel, &m_pImmediateContext); // ����̽� ����
	
	return D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, pFeatureLevels, 1, D3D11_SDK_VERSION, &m_pd3dDevice, pFeatureLevel, &m_pImmediateContext);
}

// 2) ���丮 ����
HRESULT TestUI::createFactory()
{
	//////////////////////////////////////////////////////////////////////
	// 2) ���丮 ����
	//////////////////////////////////////////////////////////////////////
	// IDXGIFactory* m_pGIFactory = nullptr;
	// IDXGISwapChain* m_pSwapChain = nullptr;
	// �Ϲ����� ���̶�� CreateDXGIFactory(IDXGIFactory, (void**)&m_pGIFactory) �� ���� �߰����� (new IDXGIFactory �ϴ� �� ó��)
	// COM(Component Object Model) ������ CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory) ó�� ��� �ؾߵ�.
	
	return CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory);
}

// 3) ����ü�� ����
HRESULT TestUI::createSwapChain()
{
	//////////////////////////////////////////////////////////////////////
	// 3) ����ü�� ����
	//////////////////////////////////////////////////////////////////////
	// IUnknown* pDevice,
	// DXGI_SWAP_CHAIN_DESC* pDesc,
	// IDXGISwapChain** ppSwapChain
	// �ĸ����(�����) ���� <-> ���� ����
	DXGI_SWAP_CHAIN_DESC Desc;
	// DXGI_SWAP_CHAIN_DESC ����ü
	// DXGI_MODE_DESC BufferDesc;
	// DXGI_SAMPLE_DESC SampleDesc;
	// DXGI_USAGE BufferUsage;
	// UINT BufferCount;
	// HWND OutputWindow;
	// BOOL Windowed;
	// DXGI_SWAP_EFFECT SwapEffect;
	// UINT Flags;

	ZeroMemory(&Desc, sizeof(DXGI_SWAP_CHAIN_DESC));

	// UINT BufferCount;
	Desc.BufferCount = 1; // �� ���� ����

	// DXGI_MODE_DESC BufferDesc; // ���� �߿�
	Desc.BufferDesc.Width = clientRect.right; // Ŭ���̾�Ʈ Width
	Desc.BufferDesc.Height = clientRect.bottom; // Ŭ���̾�Ʈ Height
	Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32��Ʈ RGBA ���
	Desc.BufferDesc.RefreshRate.Numerator = 60; // ����� �ֻ���, Frame Per Second, ���� ���� FPS�ʹ� �ٸ��� ���� 
	Desc.BufferDesc.RefreshRate.Denominator = 1; // �и� 60 / 1 == 60 frame

	// DXGI_USAGE BufferUsage;
	Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ���� ���۰� ������ ����̶�� ���� ����.

	// HWND OutputWindow;
	Desc.OutputWindow = hWnd; // �ش� �����쿡 ���

	// DXGI_SAMPLE_DESC SampleDesc;
	// ���ø��� ��(��ȣ �� �ý���, �������� �ð��׷����� �ú��� �Ͽ� �߰� �ɰԴ� ��, 1�� ������ �ƹ� �͵� ���� �Ͱ� ����.)
	// ���⼭�� �����Ӵ� ��� �Ѹ� ���̳ķ� �ؼ� ����.
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;

	// BOOL Windowed;
	Desc.Windowed = true; // â���� ���ų�(true) Ǯ ��ũ��(��üȭ�� false)���� ���ų�, Ǯ ��ũ���� Ÿ��Ʋ ������ �Ⱥ���. �ִ�ȭ�� �ٸ�.

	// UINT Flags;
	Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// DXGI_SWAP_EFFECT SwapEffect;
	// ??

	return m_pGIFactory->CreateSwapChain(m_pd3dDevice, &Desc, &m_pSwapChain);;
	

}

// 4) ���� Ÿ�ٺ� ����
HRESULT TestUI::createRenderTargetView()
{
	//////////////////////////////////////////////////////////////////////
	// 4) ���� Ÿ�ٺ� ����
	//////////////////////////////////////////////////////////////////////
	HRESULT rst;

	ID3D11Texture2D* pBackBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer); // ������ ���� 0�� ���۸� ������. ���纻�� ���� ����.
	rst = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRTV);
	pBackBuffer->Release(); // ���纻 ������

	return rst;
}

// 5) �� ��Ʈ ����
void TestUI::createViewPort()
{
	//////////////////////////////////////////////////////////////////////
	// 5) �� ��Ʈ ����
	//////////////////////////////////////////////////////////////////////
	// �� ��Ʈ�� �����ؼ� ��üȭ���� �ƴ� �� �κи� ����� �� �ִ�.
	// ex)
	// vp.Width = 100;
	// vp.Height = 100;
	// vp.TopLeftX = 100;
	// vp.TopLeftY = 100;
	// vp.MinDepth = 0.0f; // z ��
	// vp.MaxDepth = 1.0f; // z ��
	// ����ۿ��� (100, 100) ���� 100, 100 ��ŭ�� ���

	// Ŭ���̾�Ʈ���� ��ü ���
	D3D11_VIEWPORT vp;
	vp.Width = clientRect.right; 
	vp.Height = clientRect.bottom;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	
	m_pImmediateContext->RSSetViewports(1, &vp);
}