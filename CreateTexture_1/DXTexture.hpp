#pragma once
#include "Define.hpp"

class DXTexture
{
private:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	// Texture
public:
	ID3D11ShaderResourceView* m_pTextureResourceView;
	ID3D11Resource* m_pTextureResource;

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
	HRESULT Load(std::wstring _filename);
	
	ID3D11Resource* getResource()
	{
		return m_pTextureResource;
	}

	ID3D11ShaderResourceView* getResourceView()
	{
		return m_pTextureResourceView;
	}
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
	return DirectX::CreateWICTextureFromFile(m_pd3dDevice, _filename.c_str(), &m_pTextureResource, &m_pTextureResourceView);
}