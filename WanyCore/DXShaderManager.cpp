#include "DXShaderManager.hpp"



void DXShaderManager::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}

bool DXShaderManager::Load(int _key, ShaderType _type)
{
	auto it = m_ShaderList.find(_key);
	if (it != m_ShaderList.end())
	{
		return true;
	}

	DXShader* newShader = new DXShader;
	newShader->setDevice(m_pd3dDevice, m_pImmediateContext);
	if (_type == ShaderType::Mask)
	{
		newShader->setShaderFile(L"../include/core/HLSL/MaskShader.txt");
	}
	else
	{
		newShader->setShaderFile(L"../include/core/HLSL/ShapeShader.txt");
	}

	bool rst = newShader->initialize();
	if (!rst)
	{
		OutputDebugString(L"WanyCore::DXShaderManager::Failed Shader Initialize.\n");
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
			DXShader* pShader = it.second;
			if (pShader != nullptr)
			{
				pShader->release();
				delete pShader;
			}
		}
		m_ShaderList.clear();
	}

	return true;
}