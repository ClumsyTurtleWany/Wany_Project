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

	// Vertex Buffer
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	std::vector<Vertex> m_VertexList;

	// Index Buffer
	ID3D11Buffer* m_pIndexBuffer;
	std::vector<DWORD> m_IndexList;

	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;

	ID3DBlob* m_pVertexShaderCode = nullptr;
	ID3DBlob* m_pPixelShaderCode = nullptr;

	std::wstring m_wstrShaderFile;

private:
	// Texture
	DXTexture* m_pTexture;
	DXTexture* m_pTextureMask;	

private:
	bool isCreated = false;

private:
	virtual HRESULT CreateVertexBuffer();
	virtual HRESULT CreateIndexBuffer();
	virtual HRESULT CreateVertexLayout();
	virtual HRESULT CreateVertexSharder();
	virtual HRESULT CreatePixelSharder();

	virtual void initializeVertexList();
	virtual void initializeIndexList();
	
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

