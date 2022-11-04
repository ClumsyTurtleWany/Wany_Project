#pragma once
#include "DXShader.hpp"
#include "DXShaderBorder.hpp"

enum class ShaderType
{
	// No Texture
	Normal,
	// Texture
	Texture,
	// Texture + Mask
	Mask,
	Border,
	Object3D, // 2022-10-17 추가, Constant Data 사용.
	Axis3D,
};

enum class VSCodeType
{
	Texture,
	ConstantBuffer,
};

enum class PSCodeType
{
	Normal,
	Texture,
	Mask,
};

class DXShaderManager : public Singleton<DXShaderManager>
{
private:
	friend class Singleton<DXShaderManager>;

private:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

	std::map<unsigned int, DXShader*> m_ShaderList;

	std::map<VSCodeType, ID3DBlob*> m_pVertexShaderCodeMap;
	std::map<PSCodeType, ID3DBlob*> m_pPixelShaderCodeMap;

	unsigned int ShaderCnt = 0;

private:
	DXShaderManager() {};
	~DXShaderManager() { release(); };

private:
	bool LoadVSCode(VSCodeType _key, std::wstring _filename);
	bool LoadPSCode(PSCodeType _key, std::wstring _filename);

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
	bool Load(int _key, ShaderType _type = ShaderType::Texture);
	DXShader* getShader(int _key);
	bool DeleteShader(int _key);
	ID3DBlob* getVSCode(VSCodeType _key);
	ID3DBlob* getPSCode(PSCodeType _key);
	unsigned int getShaderCount();

public:
	bool initialize();
	bool frame();
	bool render();
	bool release();
};
