#pragma once
#include "WindowUI.hpp"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")


class DXDevice : public WindowUI
{
	// �������̽� -> �ϵ���� ���� ���� -> ȹ��

	// ���ҽ��� ������ ���õ� �۾��� ���. ����̽� ��ġ Ȥ�� ����̽� ��ü�� �θ�
	ID3D11Device* m_pd3dDevice = nullptr;

	// ������ ���ҽ����� ����Ͽ� ������ ó�� �� ����
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

	IDXGIFactory* m_pGIFactory = nullptr;

	// ���� ���� �� �ĸ� ���۵��� ���� �� ����.
	IDXGISwapChain* m_pSwapChain = nullptr;

	// ������ �ĸ� ���۵� �߿��� ������(���) �� ��� ���۸� ����.
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

public:

};

bool DXDevice::initialize()
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
bool DXDevice::frame()
{
	return true;
}
bool DXDevice::render()
{
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL); // m_pRTV �� �Ѹ���.
	float color[4] = { 1.0f, 0, 0, 1.0f }; // R, G, B, A �� 0 ~ 1.0���� �� 1.0 == 255
	m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);
	m_pSwapChain->Present(0, 0); // 0�� ���۸� �Ѹ���.
	return true;
}
bool DXDevice::release()
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
HRESULT DXDevice::createDevice()
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
HRESULT DXDevice::createFactory()
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
HRESULT DXDevice::createSwapChain()
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
HRESULT DXDevice::createRenderTargetView()
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
void DXDevice::createViewPort()
{
	//////////////////////////////////////////////////////////////////////
	// 5) �� ��Ʈ ����
	//////////////////////////////////////////////////////////////////////
	D3D11_VIEWPORT vp;
	vp.Width = clientRect.right;
	vp.Height = clientRect.bottom;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MaxDepth = 1.0f;
	vp.MinDepth = 0.0f;

	m_pImmediateContext->RSSetViewports(1, &vp);
}