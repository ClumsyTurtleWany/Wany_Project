#pragma once
#include "Define.hpp"

class DXTexture
{
private:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	
public:
	// Texture
	ID3D11ShaderResourceView* m_pTextureResourceView;
	ID3D11Resource* m_pTextureResource;

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
	bool Load(std::wstring _filename);
	
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

bool DXTexture::Load(std::wstring _filename)
{
	// Texture
	// ID3D11Device* d3dDevice
	// const wchar_t* fileName
	// ID3D11Resource** texture
	// ID3D11ShaderResourceView** textureView
	HRESULT rst = DirectX::CreateWICTextureFromFile(m_pd3dDevice, _filename.c_str(), &m_pTextureResource, &m_pTextureResourceView);
	if (FAILED(rst))
	{
		return false;
	}




	return true;
}