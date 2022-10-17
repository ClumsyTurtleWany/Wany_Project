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
	HRESULT rst = DirectX::CreateWICTextureFromFile(m_pd3dDevice, _filename.c_str(), (ID3D11Resource**)&m_pTextureResource, &m_pTextureResourceView);
	if (FAILED(rst))
	{
		OutputDebugString(L"WanyCore::DXTexture::Failed Create WIC Texture From File.\n");
		rst = DirectX::CreateDDSTextureFromFile(m_pd3dDevice, _filename.c_str(), (ID3D11Resource**)&m_pTextureResource, &m_pTextureResourceView);
		if (FAILED(rst))
		{
			OutputDebugString(L"WanyCore::DXTexture::Failed Create DDS Texture From File.\n");
			OutputDebugString(L"WanyCore::DXTexture::Failed Load.\n");
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