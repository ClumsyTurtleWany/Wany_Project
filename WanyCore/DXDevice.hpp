#pragma once
#include "WindowUI.hpp"
#include "Define.hpp"

// Direct X
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#include <d3dcompiler.h> // D3DCompileFromFile
#pragma comment(lib, "d3dCompiler.lib")


class DXDevice : public WindowUI
{
public:
	// 인터페이스 -> 하드웨어 직접 제어 -> 획득

	// 리소스의 생성과 관련된 작업에 사용. 디바이스 장치 혹은 디바이스 객체라 부름
	ID3D11Device* m_pd3dDevice = nullptr;

	// 생성된 리소스들을 사용하여 랜더링 처리 및 제어, 즉시 랜더링
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

	// Swap Chain의 생성과 관련된 작업에 사용.
	IDXGIFactory* m_pGIFactory = nullptr;

	// 전면 버퍼 및 후면 버퍼들을 생성 및 제어. 더블 버퍼링
	IDXGISwapChain* m_pSwapChain = nullptr;

	// Render Target View: 생성된 후면 버퍼들 중에서 랜더링(출력) 될 대상 버퍼를 지정. 
	ID3D11RenderTargetView* m_pRTV = nullptr;

	// Disable for Full Screen (Alt + Enter)
	//IDXGIAdapter* m_pAdapter = nullptr;

	// Depth Stencil View
	ID3D11Texture2D* pDSTexture = nullptr;
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr;

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();

public:
	bool PreRender();
	bool PostRender();

public:
	bool resize() override;
	bool enableFullScreen() override;
	bool disableFullScreen() override;

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

	// Depth Stencil View
	HRESULT createDepthStencilView();
};
