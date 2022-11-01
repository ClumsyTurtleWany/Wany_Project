#include "DXTexture.hpp"


void DXTexture::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}

HRESULT DXTexture::Load(std::wstring _filename)
{
	// Texture
	// ID3D11Device* d3dDevice
	// const wchar_t* fileName
	// ID3D11Resource** texture
	// ID3D11ShaderResourceView** textureView
	m_wstrFileName = _filename;
	HRESULT rst = DirectX::CreateWICTextureFromFile(m_pd3dDevice, _filename.c_str(), (ID3D11Resource**)&m_pTextureResource, &m_pTextureResourceView);
	if (FAILED(rst))
	{
		OutputDebugString(L"WanyCore::DXTexture::Failed Create WIC Texture From File.\n");
		rst = DirectX::CreateDDSTextureFromFile(m_pd3dDevice, _filename.c_str(), (ID3D11Resource**)&m_pTextureResource, &m_pTextureResourceView);
		if (FAILED(rst))
		{
			OutputDebugString(L"WanyCore::DXTexture::Failed Create DDS Texture From File.\n");
			//OutputDebugString(L"WanyCore::DXTexture::Failed Load.\n");
			std::wstring debugString = L"WanyCore::DXTexture::Failed Load(";
			debugString += _filename;
			debugString += L")\n";
			OutputDebugString(debugString.c_str());
			return rst;
		}

		return rst;
	}

	m_pTextureResource->GetDesc(&m_Desc);
	return rst;
}

ID3D11Resource* DXTexture::getResource()
{
	return m_pTextureResource;
}

ID3D11ShaderResourceView* DXTexture::getResourceView()
{
	return m_pTextureResourceView;
}

float DXTexture::getWidth()
{
	return static_cast<float>(m_Desc.Width);
}

float DXTexture::getHeight()
{
	return static_cast<float>(m_Desc.Height);
}

bool DXTexture::release()
{
	if (m_pTextureResourceView != nullptr)
	{
		m_pTextureResourceView->Release();
		m_pTextureResourceView = nullptr;
	}

	if (m_pTextureResource != nullptr)
	{
		m_pTextureResource->Release();
		m_pTextureResource = nullptr;
	}

	return true;
}

bool DXTexture::CreateRenderTarget(float _width, float _height)
{
	ZeroMemory(&m_Desc, sizeof(m_Desc));
	m_Desc.Width = _width;
	m_Desc.Height = _height;
	m_Desc.MipLevels = 1;
	m_Desc.ArraySize = 1;
	m_Desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_Desc.SampleDesc.Count = 1;
	m_Desc.SampleDesc.Quality = 0;
	m_Desc.Usage = D3D11_USAGE_DEFAULT;
	m_Desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	m_Desc.CPUAccessFlags = 0;
	m_Desc.MiscFlags = 0;

	HRESULT rst = m_pd3dDevice->CreateTexture2D(&m_Desc, NULL, &m_pTextureResource);
	if (FAILED(rst))
	{
		OutputDebugString(L"WanyCore::DXTexture::CreateRenderTarget::Failed Create Render Target Texture.\n");
		return false;
	}

	rst = m_pd3dDevice->CreateShaderResourceView(m_pTextureResource, NULL, &m_pTextureResourceView);
	if (FAILED(rst))
	{
		OutputDebugString(L"WanyCore::DXTexture::CreateRenderTarget::Failed Create Render Target Texture Resource View.\n");
		return false;
	}

	return true;
}
