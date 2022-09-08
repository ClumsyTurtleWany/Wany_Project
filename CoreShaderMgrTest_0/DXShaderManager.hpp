#pragma once
#include "DXShader.hpp"

enum class ShaderType
{
	Normal,
	Mask,
};

class DXShaderManager : public Singleton< DXShaderManager>
{
private:
	friend class Singleton<DXShaderManager>;

	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

	std::map<int, DXShader*> m_ShaderList;

private:
	DXShaderManager() {};
	~DXShaderManager() { release(); };

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
	bool Load(int _key, ShaderType _type = ShaderType::Normal);
	DXShader* getShader(int _key);

public:
	bool initialize();
	bool frame();
	bool render();
	bool release();
};
