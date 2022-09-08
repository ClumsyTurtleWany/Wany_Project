#include "DXTextureManager.hpp"


void DXTextureManager::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}

bool DXTextureManager::Load(std::wstring _filename)
{
	auto it = m_TextureList.find(_filename);
	if (it != m_TextureList.end())
	{
		return true;
	}

	DXTexture* newTexture = new DXTexture;
	newTexture->setDevice(m_pd3dDevice, m_pImmediateContext);
	HRESULT rst = newTexture->Load(_filename);
	if (FAILED(rst))
	{
		delete newTexture;
		OutputDebugString(L"WanyCore::DXTextureManager::Failed Load File.\n");
		return false;
	}

	m_TextureList.insert(std::make_pair(_filename, newTexture));

	return true;
}

//bool DXTextureManager::LoadMask(std::wstring _filename)
//{
//	auto it = m_TextureMaskList.find(_filename);
//	if (it != m_TextureMaskList.end())
//	{
//		return true;
//	}
//
//	DXTexture* newTexture = new DXTexture;
//	newTexture->setDevice(m_pd3dDevice, m_pImmediateContext);
//	HRESULT rst = newTexture->Load(_filename);
//	if (FAILED(rst))
//	{
//		delete newTexture;
//		OutputDebugString(L"WanyCore::DXTextureManager::Failed Load Mask File.\n");
//		return false;
//	}
//
//	m_TextureMaskList.insert(std::make_pair(_filename, newTexture));
//
//	return true;
//}

DXTexture* DXTextureManager::getTexture(std::wstring _filename)
{
	auto it = m_TextureList.find(_filename);
	if (it != m_TextureList.end())
	{
		return it->second;
	}
	return nullptr;
}

//DXTexture* DXTextureManager::getTextureMask(std::wstring _filename)
//{
//	auto it = m_TextureMaskList.find(_filename);
//	if (it != m_TextureMaskList.end())
//	{
//		return it->second;
//	}
//	return nullptr;
//}

bool DXTextureManager::initialize()
{
	return true;
}

bool DXTextureManager::frame()
{
	return true;
}

bool DXTextureManager::render()
{
	return true;
}

bool DXTextureManager::release()
{
	if (!m_TextureList.empty())
	{
		for (auto it : m_TextureList)
		{
			DXTexture* pTexture = it.second;
			if (pTexture != nullptr)
			{
				pTexture->release();
				delete pTexture;
			}
		}
		m_TextureList.clear();
	}

	/*if (!m_TextureMaskList.empty())
	{
		for (auto it : m_TextureMaskList)
		{
			DXTexture* pTexture = it.second;
			if (pTexture != nullptr)
			{
				pTexture->release();
				delete pTexture;
			}
		}
		m_TextureMaskList.clear();
	}*/

	return true;
}