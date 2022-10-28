#include "DXTextureRenderTarget.hpp"

void DXTextureRenderTarget::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}

bool DXTextureRenderTarget::create(float _width, float _height)
{
	// View Port
	m_viewPort.TopLeftX = 0;
	m_viewPort.TopLeftY = 0;
	m_viewPort.Width = _width;
	m_viewPort.Height = _height;
	m_viewPort.MinDepth = 0.0f;
	m_viewPort.MaxDepth = 1.0f;

	// Texture Render Target View
	if (m_pTexture == nullptr)
	{
		m_pTexture = new DXTexture;
		m_pTexture->setDevice(m_pd3dDevice, m_pImmediateContext);
		if (!m_pTexture->CreateRenderTarget(_width, _height))
		{
			OutputDebugString(L"WanyCore::DXTextureRenderTarget::create::Failed Create Render Target Texture.\n");
			delete m_pTexture;
			m_pTexture = nullptr;
			return false;
		}
	}

	HRESULT rst = m_pd3dDevice->CreateRenderTargetView(m_pTexture->getResource(), NULL, &m_pRenderTargetView);
	if (FAILED(rst))
	{
		OutputDebugString(L"WanyCore::DXTextureRenderTarget::create::Failed Create Render Target View.\n");
		return false;
	}

	// Depth Stencil View
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = _width;
	desc.Height = _height;
	desc.MipLevels = 1; // 0���� �ϸ� 9�ܰ� ���� ����
	desc.ArraySize = 1; // 1���� ����
	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; //DXGI_FORMAT_R24G8_TYPELESS; // 32bit, 24bit�� Z����(Depth)�� ����ϰ�, 8bit�� ���ٽ� ���۷� ��� �ϰڴ�.
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // �߿�! ��� ���� �� ������ ���ϴ� ��.
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	rst = m_pd3dDevice->CreateTexture2D(&desc, NULL, &m_pDSTexture);
	if (FAILED(rst))
	{
		OutputDebugString(L"WanyCore::DXTextureRenderTarget::create::Failed Create Depth Stencil Texture.\n");
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC DSdesc;
	ZeroMemory(&DSdesc, sizeof(DSdesc));
	DSdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // Depth�� ��ֶ����� ��������, ���ٽ��� ���������� ����. Texture ������ ��Ʈ�� ���� �����.
	DSdesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DSdesc.Flags = 0;

	rst = m_pd3dDevice->CreateDepthStencilView(m_pDSTexture, &DSdesc, &m_pDepthStencilView);
	if (FAILED(rst))
	{
		OutputDebugString(L"WanyCore::DXTextureRenderTarget::create::Failed Create Depth Stencil View.\n");
		return false;
	}

	// Create Shader
	if (m_pShader == nullptr)
	{
		m_pShader = new DXShader;
		m_pShader->setDevice(m_pd3dDevice, m_pImmediateContext);
		m_pShader->setVSCode(DXShaderManager::getInstance()->getVSCode(VSCodeType::ConstantBuffer));
		m_pShader->setPSCode(DXShaderManager::getInstance()->getPSCode(PSCodeType::Texture));
		m_pShader->initialize();
		m_pShader->setTexture(m_pTexture);
	}

	return true;
}

bool DXTextureRenderTarget::begin()
{
	ID3D11ShaderResourceView* resourceView = NULL;
	m_pImmediateContext->PSSetShaderResources(0, 1, &resourceView); // �������� 0��

	// Save Old
	UINT nViewPorts = 1;
	m_pImmediateContext->RSGetViewports(&nViewPorts, m_OldViewPort);
	m_pImmediateContext->OMGetRenderTargets(1, &m_pOldRenderTargetView, &m_pOldDepthStencilView);

	if (m_pOldRenderTargetView != nullptr)
	{
		float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // R, G, B, A �� 0 ~ 1.0���� �� 1.0 == 255
		m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, color);
	}

	if (m_pOldDepthStencilView != nullptr)
	{
		m_pImmediateContext->ClearDepthStencilView(m_pOldDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	// Apply New
	ID3D11RenderTargetView* pRenderTargetView = nullptr;
	m_pImmediateContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);

	//m_pImmediateContext->OMSetRenderTargets(0, nullptr, nullptr);
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // R, G, B, A �� 0 ~ 1.0���� �� 1.0 == 255
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, color);
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_pImmediateContext->RSSetViewports(1, &m_viewPort);

	return true;
}

bool DXTextureRenderTarget::end()
{
	//ID3D11ShaderResourceView* resourceView = NULL;
	//m_pImmediateContext->PSSetShaderResources(0, 1, &resourceView); // �������� 0��

	ID3D11RenderTargetView* pRenderTargetView = nullptr;
	m_pImmediateContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);
	m_pImmediateContext->OMSetRenderTargets(1, &m_pOldRenderTargetView, m_pOldDepthStencilView);

	m_pImmediateContext->RSSetViewports(1, &m_OldViewPort[0]);

	if (m_pOldRenderTargetView != nullptr)
	{
		m_pOldRenderTargetView->Release();
		m_pOldRenderTargetView = nullptr;
	}

	if (m_pOldDepthStencilView != nullptr)
	{
		m_pOldDepthStencilView->Release();
		m_pOldDepthStencilView = nullptr;
	}

	return true;
}

bool DXTextureRenderTarget::render()
{
	m_pShader->render();
	return true;
}

bool DXTextureRenderTarget::release()
{
	if (m_pRenderTargetView != nullptr)
	{
		m_pRenderTargetView->Release();
		m_pRenderTargetView = nullptr;
	}

	if (m_pTexture != nullptr)
	{
		m_pTexture->release();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pDepthStencilView != nullptr)
	{
		m_pDepthStencilView->Release();
		m_pDepthStencilView = nullptr;
	}

	if (m_pDSTexture != nullptr)
	{
		m_pDSTexture->Release();
		m_pDSTexture = nullptr;
	}

	if (m_pOldRenderTargetView != nullptr)
	{
		m_pOldRenderTargetView->Release();
		m_pOldRenderTargetView = nullptr;
	}

	if (m_pOldDepthStencilView != nullptr)
	{
		m_pOldDepthStencilView->Release();
		m_pOldDepthStencilView = nullptr;
	}

	if (m_pShader != nullptr)
	{
		m_pShader->release();
		delete m_pShader;
		m_pShader = nullptr;
	}

	return true;
}