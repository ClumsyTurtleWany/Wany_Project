#pragma once
#include "DXShader.hpp"

class DXShaderManager
{
private:
	static DXShaderManager* shaderMgr;

private:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

	std::map<int, DXShader*> m_ShaderList;

private:
	DXShaderManager() {};
	~DXShaderManager()
	{
		if (shaderMgr != nullptr)
		{
			delete shaderMgr;
			shaderMgr = nullptr;
		}
	};

public:
	static DXShaderManager* getShaderMgr()
	{
		if (shaderMgr == nullptr)
		{
			shaderMgr = new DXShaderManager;
		}
		return shaderMgr;
	}

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
	bool Load(int _key);
	DXShader* getShader(int _key);

public:
	bool initialize();
	bool frame();
	bool render();
	bool release();
};

DXShaderManager* DXShaderManager::shaderMgr = nullptr;

void DXShaderManager::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}

bool DXShaderManager::Load(int _key)
{
	auto it = m_ShaderList.find(_key);
	if (it != m_ShaderList.end())
	{
		return it->second;
	}

	DXShader* newShader = new DXShader;
	newShader->setDevice(m_pd3dDevice, m_pImmediateContext);
	bool rst = newShader->initialize();
	if (!rst)
	{
		return false;
	}

	m_ShaderList.insert(std::make_pair(_key, newShader));

	return rst;
}

DXShader* DXShaderManager::getShader(int _key)
{
	auto it = m_ShaderList.find(_key);
	if (it != m_ShaderList.end())
	{
		return it->second;
	}
	return nullptr;
}


bool DXShaderManager::initialize()
{
	return true;
}

bool DXShaderManager::frame()
{
	return true;
}

bool DXShaderManager::render()
{
	return true;
}

bool DXShaderManager::release()
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