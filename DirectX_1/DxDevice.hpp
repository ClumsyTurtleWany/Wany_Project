#pragma once
#include "WindowUI.hpp"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")


class DXDevice : public WindowUI
{
	// 인터페이스 -> 하드웨어 직접 제어 -> 획득

	// 리소스의 생성과 관련된 작업에 사용. 디바이스 장치 혹은 디바이스 객체라 부름
	ID3D11Device* m_pd3dDevice = nullptr;

	// 생성된 리소스들을 사용하여 랜더링 처리 및 제어
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

	IDXGIFactory* m_pGIFactory = nullptr;

	// 전면 버퍼 및 후면 버퍼들을 생성 및 제어.
	IDXGISwapChain* m_pSwapChain = nullptr;

	// 생성된 후면 버퍼들 중에서 랜더링(출력) 될 대상 버퍼를 지정.
	ID3D11RenderTargetView* m_pRTV = nullptr;

public:
	bool initialize() override;
	bool frame() override;
	bool render() override;
	bool release() override;

public:
	// 1) 디바이스 생성
	HRESULT createDevice();
	// 2) 팩토리 생성
	HRESULT createFactory();
	// 3) 스왑체인 생성
	HRESULT createSwapChain();
	// 4) 랜더 타겟뷰 생성
	HRESULT createRenderTargetView();
	// 5) 뷰 포트 설정
	void createViewPort();

public:

};

bool DXDevice::initialize()
{
	//////////////////////////////////////////////////////////////////////
	// 1) 디바이스 생성
	//////////////////////////////////////////////////////////////////////

	if (FAILED(createDevice())) // 0도 성공으로 들어가 있어서 SUCCEED FAILED로만 사용할 것.
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////
	// 2) 팩토리 생성
	//////////////////////////////////////////////////////////////////////

	if (FAILED(createFactory()))
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////
	// 3) 스왑체인 생성
	//////////////////////////////////////////////////////////////////////

	if (FAILED(createSwapChain()))
	{
		return false;
	}


	//////////////////////////////////////////////////////////////////////
	// 4) 랜더 타겟뷰 생성
	//////////////////////////////////////////////////////////////////////

	if (FAILED(createRenderTargetView()))
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////
	// 5) 뷰 포트 설정
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
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL); // m_pRTV 에 뿌린다.
	float color[4] = { 1.0f, 0, 0, 1.0f }; // R, G, B, A 순 0 ~ 1.0사이 값 1.0 == 255
	m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);
	m_pSwapChain->Present(0, 0); // 0번 버퍼를 뿌린다.
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


// 1) 디바이스 생성
HRESULT DXDevice::createDevice()
{
	//////////////////////////////////////////////////////////////////////
	// 1) 디바이스 생성
	//////////////////////////////////////////////////////////////////////
	//
	// HRESULT rst; // Dx의 모든 반환값은 HRESULT 사용
	// D3D_FEATURE_LEVEL* pFeatureLevel = nullptr; // 안받아도 됨.
	// IDXGIAdapter* pAdapter = nullptr; // 그래픽 카드, nullptr을 넣으면 현재 사용 중인 그래픽 카드 사용 하겠다
	// D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE; // 기본은 D3D_DRIVER_TYPE_HARDWARE (GPU 처리)를 쓰는데 그래픽 카드가 성능이 좋지 않거나 기능을 지원하지 않으면, Software(CPU 처리) 등을 사용
	// HMODULE Software = NULL; // DirverType과 마찬가지로 CPU 처리를 위한 것. NULL은 사용 안함.
	// UINT Flags = 0;
	// D3D_FEATURE_LEVEL pFeatureLevels[] = { /*D3D_FEATURE_LEVEL_12_0,*/ D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 }; // 12를 사용하되 지원 안되면 11, 10 순으로
	// UINT FeatureLevels = 2; // pFeatureLevels 인자 갯수
	// UINT SDKVersion = D3D11_SDK_VERSION; // 무조건 최신으로 넣을 것
	// ID3D11Device** ppDevice;
	// rst = D3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, &m_pd3dDevice, pFeatureLevel, &m_pImmediateContext); // 디바이스 생성

	// 축약 버전
	//HRESULT rst; // Dx의 모든 반환값은 HRESULT 사용
	D3D_FEATURE_LEVEL* pFeatureLevel = nullptr;
	D3D_FEATURE_LEVEL pFeatureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	ID3D11Device** ppDevice;
	//rst = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, pFeatureLevels, 1, D3D11_SDK_VERSION, &m_pd3dDevice, pFeatureLevel, &m_pImmediateContext); // 디바이스 생성

	return D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, pFeatureLevels, 1, D3D11_SDK_VERSION, &m_pd3dDevice, pFeatureLevel, &m_pImmediateContext);
}

// 2) 팩토리 생성
HRESULT DXDevice::createFactory()
{
	//////////////////////////////////////////////////////////////////////
	// 2) 팩토리 생성
	//////////////////////////////////////////////////////////////////////
	// IDXGIFactory* m_pGIFactory = nullptr;
	// IDXGISwapChain* m_pSwapChain = nullptr;
	// 일반적인 놈이라면 CreateDXGIFactory(IDXGIFactory, (void**)&m_pGIFactory) 로 생성 했겠지만 (new IDXGIFactory 하는 것 처럼)
	// COM(Component Object Model) 에서는 CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory) 처럼 사용 해야됨.

	return CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory);
}

// 3) 스왑체인 생성
HRESULT DXDevice::createSwapChain()
{
	//////////////////////////////////////////////////////////////////////
	// 3) 스왑체인 생성
	//////////////////////////////////////////////////////////////////////
	// IUnknown* pDevice,
	// DXGI_SWAP_CHAIN_DESC* pDesc,
	// IDXGISwapChain** ppSwapChain
	// 후면버퍼(백버퍼) 생성 <-> 전면 버퍼
	DXGI_SWAP_CHAIN_DESC Desc;
	// DXGI_SWAP_CHAIN_DESC 구조체
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
	Desc.BufferCount = 1; // 백 버퍼 개수

	// DXGI_MODE_DESC BufferDesc; // 가장 중요
	Desc.BufferDesc.Width = clientRect.right; // 클라이언트 Width
	Desc.BufferDesc.Height = clientRect.bottom; // 클라이언트 Height
	Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32비트 RGBA 사용
	Desc.BufferDesc.RefreshRate.Numerator = 60; // 모니터 주사율, Frame Per Second, 게임 내의 FPS와는 다르게 생각 
	Desc.BufferDesc.RefreshRate.Denominator = 1; // 분모 60 / 1 == 60 frame

	// DXGI_USAGE BufferUsage;
	Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 위의 버퍼가 랜더링 대상이라는 것을 지정.

	// HWND OutputWindow;
	Desc.OutputWindow = hWnd; // 해당 윈도우에 출력

	// DXGI_SAMPLE_DESC SampleDesc;
	// 샘플링할 수(신호 및 시스템, 연속적인 시간그래프를 시분할 하여 잘게 쪼게는 것, 1로 나누면 아무 것도 안한 것과 같다.)
	// 여기서는 프레임당 몇번 뿌릴 것이냐로 해석 가능.
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;

	// BOOL Windowed;
	Desc.Windowed = true; // 창모드로 띄울거냐(true) 풀 스크린(전체화면 false)으로 띄울거냐, 풀 스크린은 타이틀 라인이 안보임. 최대화와 다름.

	// UINT Flags;
	Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// DXGI_SWAP_EFFECT SwapEffect;
	// ??

	return m_pGIFactory->CreateSwapChain(m_pd3dDevice, &Desc, &m_pSwapChain);;


}

// 4) 랜더 타겟뷰 생성
HRESULT DXDevice::createRenderTargetView()
{
	//////////////////////////////////////////////////////////////////////
	// 4) 랜더 타겟뷰 생성
	//////////////////////////////////////////////////////////////////////
	HRESULT rst;

	ID3D11Texture2D* pBackBuffer = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer); // 위에서 만든 0번 버퍼를 가져옴. 복사본이 오는 것임.
	rst = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRTV);
	pBackBuffer->Release(); // 복사본 릴리즈

	return rst;
}

// 5) 뷰 포트 설정
void DXDevice::createViewPort()
{
	//////////////////////////////////////////////////////////////////////
	// 5) 뷰 포트 설정
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