#pragma once
#include "DXShader.hpp"

enum class ShaderType
{
	Normal,
	Mask,
};

template <typename T>
class DXShaderManager : public Singleton<DXShaderManager<T>>
{
private:
	friend class Singleton<DXShaderManager>;

	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

	std::map<T, DXShader*> m_ShaderList;

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

template <typename T>
void DXShaderManager<T>::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}

template <typename T>
bool DXShaderManager<T>::Load(int _key, ShaderType _type)
{
	auto it = m_ShaderList.find(_key);
	if (it != m_ShaderList.end())
	{
		return it->second;
	}

	DXShader* newShader = new DXShader;
	newShader->setDevice(m_pd3dDevice, m_pImmediateContext);
	if (_type == ShaderType::Mask)
	{
		newShader->setShaderFile(L"MaskShader.txt");
	}
	else
	{
		newShader->setShaderFile(L"../HLSL/ShapeShader.txt");
	}

	bool rst = newShader->initialize();
	if (!rst)
	{
		return false;
	}

	m_ShaderList.insert(std::make_pair(_key, newShader));

	return rst;
}

template <typename T>
DXShader* DXShaderManager<T>::getShader(int _key)
{
	auto it = m_ShaderList.find(_key);
	if (it != m_ShaderList.end())
	{
		return it->second;
	}
	return nullptr;
}

template <typename T>
bool DXShaderManager<T>::initialize()
{
	return true;
}

template <typename T>
bool DXShaderManager<T>::frame()
{
	return true;
}

template <typename T>
bool DXShaderManager<T>::render()
{
	return true;
}

template <typename T>
bool DXShaderManager<T>::release()
{
	if (!m_ShaderList.empty())
	{
		for (auto it : m_ShaderList)
		{
			delete it.second;
		}
	}

	return true;
}