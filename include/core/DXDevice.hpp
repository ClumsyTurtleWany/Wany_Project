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
	// �������̽� -> �ϵ���� ���� ���� -> ȹ��

	// ���ҽ��� ������ ���õ� �۾��� ���. ����̽� ��ġ Ȥ�� ����̽� ��ü�� �θ�
	ID3D11Device* m_pd3dDevice = nullptr;

	// ������ ���ҽ����� ����Ͽ� ������ ó�� �� ����, ��� ������
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

	// Swap Chain�� ������ ���õ� �۾��� ���.
	IDXGIFactory* m_pGIFactory = nullptr;

	// ���� ���� �� �ĸ� ���۵��� ���� �� ����. ���� ���۸�
	IDXGISwapChain* m_pSwapChain = nullptr;

	// Render Target View: ������ �ĸ� ���۵� �߿��� ������(���) �� ��� ���۸� ����. 
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

	// Depth Stencil View
	HRESULT createDepthStencilView();
};
