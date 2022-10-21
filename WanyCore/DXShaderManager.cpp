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
		return false;
	}

	DXShader* newShader = nullptr;
	if (_type == ShaderType::Border)
	{
		newShader = new DXShaderBorder;
	}
	else
	{ 
		newShader = new DXShader;
	}
	
	newShader->setDevice(m_pd3dDevice, m_pImmediateContext);
	if (_type == ShaderType::Mask)
	{
		// 텍스처 출력 가능. 마스크 Discard
		newShader->setShaderFile(L"../include/core/HLSL/MaskShader.txt");
	}
	else if (_type == ShaderType::Texture)
	{
		// 텍스처 출력 가능.
		newShader->setShaderFile(L"../include/core/HLSL/TextureShader.txt");
	}
	else if (_type == ShaderType::Object3D)
	{
		// Constant Data 이용하여 쉐이더에서 매트릭스 계산. 텍스처 출력 가능.
		newShader->setShaderFile(L"../include/core/HLSL/Textured3D.txt");
		newShader->setCreateConstantFlag(true);
	}
	else if (_type == ShaderType::Axis3D)
	{
		// Constant Data 이용하여 쉐이더에서 매트릭스 계산. 텍스처 출력 가능.
		newShader->setShaderFile(L"../include/core/HLSL/DefaultObject.txt");
		newShader->setCreateConstantFlag(true);
	}
	else
	{
		// 다이렉트로 픽셀 뿌림. 텍스처 출력 불가.
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

bool DXShaderManager::DeleteShader(int _key)
{
	auto it = m_ShaderList.find(_key);
	if (it != m_ShaderList.end())
	{
		DXShader* pShader = it->second;
		pShader->release();
		pShader = nullptr;
		m_ShaderList.erase(_key);
		return true;
	}
	return false;
}

bool DXShaderManager::initialize()
{
	return true;
}

bool DXShaderManager::frame()
{
	for (auto it : m_ShaderList)
	{
		it.second->frame();
	}
	return true;
}

bool DXShaderManager::render()
{
	for (auto it : m_ShaderList)
	{
		it.second->render();
	}
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