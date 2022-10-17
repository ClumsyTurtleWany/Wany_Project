#pragma once
#include "DXDevice.hpp"
#include "DXTexture.hpp"
#include "Define.hpp"
#include "Vertex.hpp"
#include "Matrix.hpp"

struct ConstantBufferData
{
	
};

class DXShader
{
protected:
	// Device
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

protected:
	// Vertex Buffer
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11InputLayout* m_pVertexLayout = nullptr;
	std::vector<Vertex> m_VertexList;

	// Index Buffer
	ID3D11Buffer* m_pIndexBuffer = nullptr;
	std::vector<DWORD> m_IndexList;

	// Constant Buffer
	ID3D11Buffer* m_pConstantBuffer = nullptr;
	ConstantBufferData m_ConstantData;

	// Shader
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;

	ID3DBlob* m_pVertexShaderCode = nullptr;
	ID3DBlob* m_pPixelShaderCode = nullptr;

	std::wstring m_wstrShaderFile;

	D3D11_PRIMITIVE_TOPOLOGY m_Topology;

protected:
	// Texture
	DXTexture* m_pTexture;
	DXTexture* m_pTextureMask;	

protected:
	bool isCreated = false;

protected:
	virtual HRESULT CreateVertexBuffer();
	virtual HRESULT CreateIndexBuffer();
	virtual HRESULT CreateConstantBuffer();
	virtual HRESULT CreateVertexLayout();
	virtual HRESULT CreateVertexSharder();
	virtual HRESULT CreatePixelSharder();

	virtual void initializeVertexList();
	virtual void initializeIndexList();
	virtual void initializeConstantData();
	
public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
	void setTexture(DXTexture* _texture);
	void setColor(const Vector4f& _color);
	void setTextureMask(DXTexture* _texture);
	void setShaderFile(std::wstring _file);
	std::vector<Vertex>* getVertexList();
	bool updateVertexList(std::vector<Vertex>* _list);
	bool updateIndexList(std::vector<DWORD>* _list);
	bool updateConstantData(ConstantBufferData* _data);
	
public:
	float getTextureWidth();
	float getTextureHeight();

};

