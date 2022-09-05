#pragma once
#include "Define.hpp"

class DXTexture
{
private:
	ID3D11Device*				m_pd3dDevice = nullptr;
	ID3D11DeviceContext*		m_pImmediateContext = nullptr;
	
private:
	// Texture
	ID3D11ShaderResourceView*	m_pTextureResourceView;
	//ID3D11Resource*			m_pTextureResource;
	ID3D11Texture2D*			m_pTextureResource;
	D3D11_TEXTURE2D_DESC		m_Desc;

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
	HRESULT Load(std::wstring _filename);
	
	ID3D11Resource* getResource();
	ID3D11ShaderResourceView* getResourceView();

	float getWidth();
	float getHeight();
	
};

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
	return m_Desc.Width;
}

float DXTexture::getHeight()
{
	return m_Desc.Height;
}
