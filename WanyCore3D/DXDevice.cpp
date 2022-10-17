#include "DXDevice.hpp"
#include "DXWriter.hpp"

bool DXDevice::resize()
{
	// ������ ũ�� ���� �޽��� ����(WM_SIZE)
	// ���� ������ ����Ÿ�ϰ� ���� ���ٽ� ������ ���� �� �Ҹ�
	if (m_pd3dDevice == nullptr)
	{
		return false;
	}

	DXWriter::getInstance()->releaseDXResource();

	m_pImmediateContext->OMSetRenderTargets(0, nullptr, NULL);
	m_pRTV->Release();
	m_pRTV = nullptr;
	 
	// ����� �������� ũ�⸦ ��� �� ������ ũ�⸦ �� ����.
	DXGI_SWAP_CHAIN_DESC desc;
	m_pSwapChain->GetDesc(&desc);
	HRESULT rst = m_pSwapChain->ResizeBuffers(desc.BufferCount, clientRect.right, clientRect.bottom, desc.BufferDesc.Format, 0);
	if (FAILED(rst))
	{
		return false;
	}

	// ����� �� ������ ũ�⸦ ��� ����Ÿ�� �並 �ٽ� ���� �� ����.
	createRenderTargetView();
	
	// �Ҹ��ߴ� ���� ���ٽ� ���ۿ� ���� ���ٽ� �� �ٽ� ���� �� ����
	// ����Ʈ �� ����.
	createViewPort();

	IDXGISurface* pBackBuffer;
	rst = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);
	if (SUCCEEDED(rst))
	{
		if (!DXWriter::getInstance()->setBuffer(pBackBuffer))
		{
			OutputDebugString(L"WanyCore::DXDevice::resize::Failed Set Buffer To DXWriter.\n");
			return false;
		}
		pBackBuffer->Release();
	}
	DXWriter::getInstance()->createDXResource();

	return true;
}

bool DXDevice::enableFullScreen()
{
	HRESULT rst = m_pGIFactory->MakeWindowAssociation(NULL, 0);
	if (FAILED(rst))
	{
		return false;
	}

	return true;
}

bool DXDevice::disableFullScreen()
{
	//HRESULT rst = m_pGIFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);
	HRESULT rst = m_pGIFactory->MakeWindowAssociation(NULL, DXGI_MWA_NO_ALT_ENTER);
	if (FAILED(rst))
	{
		return false;
	}

	//rst = m_pSwapChain->SetFullscreenState(TRUE, NULL); // ��üȭ�� ���
	rst = m_pSwapChain->SetFullscreenState(FALSE, NULL); // â ���
	if (FAILED(rst))
	{
		return false;
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
	// IDXGIAdapter* pAdapter = nullptr; // �׷��� ī��, nullptr�� ������ ���� ��� ���� �׷��� ī�� ��� �ϰڴ�
	// D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE; // �⺻�� D3D_DRIVER_TYPE_HARDWARE (GPU ó��)�� ���µ� �׷��� ī�尡 ������ ���� �ʰų� ����� �������� ������, Software(CPU ó��) ���� ���
	// HMODULE Software = NULL; // DirverType�� ���������� CPU ó���� ���� ��. NULL�� ��� ����.
	// UINT Flags = 0;
	// D3D_FEATURE_LEVEL pFeatureLevels[] = { /*D3D_FEATURE_LEVEL_12_0,*/ D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 }; // 12�� ����ϵ� ���� �ȵǸ� 11, 10 ������
	// UINT FeatureLevels = 2; // pFeatureLevels ���� ����
	// UINT SDKVersion = D3D11_SDK_VERSION; // ������ �ֽ����� ���� ��
	// ID3D11Device** ppDevice;
	// D3D_FEATURE_LEVEL* pFeatureLevel = nullptr; // �ȹ޾Ƶ� ��.
	// rst = D3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, &m_pd3dDevice, pFeatureLevel, &m_pImmediateContext); // ����̽� ����

	// ��� ����
	//HRESULT rst; // Dx�� ��� ��ȯ���� HRESULT ���
	D3D_FEATURE_LEVEL* pFeatureLevel = nullptr;
	D3D_FEATURE_LEVEL pFeatureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	//ID3D11Device** ppDevice;
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT; // �⺻�� 0�ε�, �� �÷��׸� �־�� ���� Ÿ�� ������ ������ �ȴ�.
#ifdef _DEBUG 
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif 
	//rst = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, pFeatureLevels, 1, D3D11_SDK_VERSION, &m_pd3dDevice, pFeatureLevel, &m_pImmediateContext); // ����̽� ����

	// 2022-10-11 ���� ����
	//return D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, pFeatureLevels, 1, D3D11_SDK_VERSION, &m_pd3dDevice, pFeatureLevel, &m_pImmediateContext);

	// 2022-10-11 ���� Full Screen Disable �׽�Ʈ ����
	IDXGIAdapter* pAdapter = nullptr;
	HRESULT rst = m_pGIFactory->EnumAdapters(0, &pAdapter);
	if (FAILED(rst))
	{
		return D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, pFeatureLevels, 1, D3D11_SDK_VERSION, &m_pd3dDevice, pFeatureLevel, &m_pImmediateContext);
	}
	else
	{
		D3D_DRIVER_TYPE driverTypes[] = { D3D_DRIVER_TYPE_HARDWARE,	D3D_DRIVER_TYPE_REFERENCE, D3D_DRIVER_TYPE_WARP };
		UINT DriverTypeNum = sizeof(driverTypes) / sizeof(driverTypes[0]);
		/*for (UINT driverTypeIdx = 0; driverTypeIdx < DriverTypeNum; driverTypeIdx++)
		{
			D3D_DRIVER_TYPE driverType = driverTypes[driverTypeIdx];
			rst = D3D11CreateDevice(pAdapter, driverType, NULL, createDeviceFlags, pFeatureLevels, 1, D3D11_SDK_VERSION, &m_pd3dDevice, pFeatureLevel, &m_pImmediateContext);
			if (FAILED(rst))
			{
				continue;
			}
			else
			{
				break;
			}
		}*/
		rst = D3D11CreateDevice(pAdapter, D3D_DRIVER_TYPE_UNKNOWN, NULL, createDeviceFlags, pFeatureLevels, 1, D3D11_SDK_VERSION, &m_pd3dDevice, pFeatureLevel, &m_pImmediateContext);


		return rst;
	}
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
	Desc.BufferDesc.Width = clientRect.right; // Ŭ���̾�Ʈ Width // Ŭ���̾�Ʈ ũ�⺸�� �۰� ����� �ȵ�.
	Desc.BufferDesc.Height = clientRect.bottom; // Ŭ���̾�Ʈ Height
	Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32��Ʈ RGBA ���
	Desc.BufferDesc.RefreshRate.Numerator = 60; // ����� �ֻ���
	Desc.BufferDesc.RefreshRate.Denominator = 1; // �и�, Numerator / Denominator == 60 / 1 == 60 Hz

	// DXGI_USAGE BufferUsage;
	// ���� ���۰� ������ ����̶�� ���� ����. 
	// ����ü���� ���۸� �����Ϸ��� �ݵ�� DXGI_USAGE_RENDER_TARGET_OUTPUT �̾�� ��.
	Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

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
	// ������ �ø��� ���� �� ���۸� �������� �������� �����ϴ� Ŭ����
	// DXGI_SWAP_EFFECT_DISCARD = 0 : Present ȣ�� �� �� ���� ���� ����
	// DXGI_SWAP_EFFECT_SEQUENTIAL = 1 : Present ȣ�� �� �� ���� ���� ����
	// �÷��״� ��Ƽ ���ø��� �Բ� ��� �Ұ�!

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
	vp.Width = static_cast<float>(clientRect.right);
	vp.Height = static_cast<float>(clientRect.bottom);
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MaxDepth = 1.0f;
	vp.MinDepth = 0.0f;

	m_pImmediateContext->RSSetViewports(1, &vp);
}

bool DXDevice::initialize()
{
	//////////////////////////////////////////////////////////////////////
	// 0) ���丮 ����, ������ 2������ ���� ������ ���� �����ص� �����ϰ�, Full Screen ���� ���� Adapter ������ ���� �ʿ�.
	//////////////////////////////////////////////////////////////////////
	if (FAILED(createFactory()))
	{
		OutputDebugString(L"WanyCore::DXDevice::Failed Create Factory.\n");
		return false;
	}

	//////////////////////////////////////////////////////////////////////
	// 1) ����̽� ����
	//////////////////////////////////////////////////////////////////////

	if (FAILED(createDevice())) // 0�� �������� �� �־ SUCCEED or FAILED�θ� ����� ��.
	{
		OutputDebugString(L"WanyCore::DXDevice::Failed Create Device.\n");
		return false;
	}

	////////////////////////////////////////////////////////////////////////
	//// 2) ���丮 ����
	////////////////////////////////////////////////////////////////////////
	//if (FAILED(createFactory()))
	//{
	//	OutputDebugString(L"WanyCore::DXDevice::Failed Create Factory.\n");
	//	return false;
	//}

	//////////////////////////////////////////////////////////////////////
	// 3) ����ü�� ����
	//////////////////////////////////////////////////////////////////////

	if (FAILED(createSwapChain()))
	{
		OutputDebugString(L"WanyCore::DXDevice::Failed Create Swap Chain.\n");
		return false;
	}


	//////////////////////////////////////////////////////////////////////
	// 4) ���� Ÿ�ٺ� ����
	//////////////////////////////////////////////////////////////////////

	if (FAILED(createRenderTargetView()))
	{
		OutputDebugString(L"WanyCore::DXDevice::Failed Create Render Target View.\n");
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
	return true;
}

bool DXDevice::release()
{
	if (m_pRTV != nullptr)
	{
		m_pRTV->Release();
		m_pRTV = nullptr;
	}

	if (m_pSwapChain != nullptr)
	{
		m_pSwapChain->Release();
		m_pSwapChain = nullptr;
	}

	if (m_pGIFactory != nullptr)
	{
		m_pGIFactory->Release();
		m_pGIFactory = nullptr;
	}

	if (m_pImmediateContext != nullptr)
	{
		m_pImmediateContext->ClearState();
		m_pImmediateContext->Release();
		m_pImmediateContext = nullptr;
	}

	if (m_pd3dDevice != nullptr)
	{
		m_pd3dDevice->Release();
		m_pd3dDevice = nullptr;
	}

	return true;
}