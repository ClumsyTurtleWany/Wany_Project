#pragma once
#include "DXDevice.hpp"
#include "DXTexture.hpp"
#include "Define.hpp"
#include "Vertex.hpp"

class DXShader
{
private:
	// Device
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

private:
	// Shader
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;

	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;

	std::wstring m_wstrShaderFile;
	ID3DBlob* m_pVertexShaderCode = nullptr;
	ID3DBlob* m_pPixelShaderCode = nullptr;

private:
	// Texture
	DXTexture* m_pTexture;
	DXTexture* m_pTextureMask;
	
private:
	std::vector<Vertex> m_VertexList;

private:
	bool isCreated = false;

private:
	HRESULT CreateVertexBuffer();
	HRESULT CreateVertexLayout();
	HRESULT CreateVertexSharder();
	HRESULT CreatePixelSharder();
	

public:
	bool initialize();
	bool frame();
	bool render();
	bool release();

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
	void setVertexList(const std::vector<Vertex>& _target);
	void setTexture(DXTexture* _texture);
	void setTextureMask(DXTexture* _texture);
	void setShaderFile(std::wstring _file);
	
public:
	float getTextureWidth();
	float getTextureHeight();

};

