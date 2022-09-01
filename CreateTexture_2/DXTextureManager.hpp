#pragma once
#include "DXTexture.hpp"

class DXTextureManager : public BaseSingleton<DXTextureManager>
{
private:
	friend class BaseSingleton<DXTextureManager>;

	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

	std::map<Texture_Key, DXTexture*> m_TextureList;

private:
	DXTextureManager() {};
	~DXTextureManager() { release(); };

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
	bool Load(Texture_Key _key, std::wstring _filename);
	DXTexture* getTexture(Texture_Key _key);

public:
	bool initialize();
	bool frame();
	bool render();
	bool release();
};

void DXTextureManager::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}

bool DXTextureManager::Load(Texture_Key _key, std::wstring _filename)
{
	DXTexture* newTexture = new DXTexture;
	newTexture->setDevice(m_pd3dDevice, m_pImmediateContext);
	HRESULT rst = newTexture->Load(_filename);
	if (FAILED(rst))
	{
		return false;
	}

	m_TextureList.insert(std::make_pair(_key, newTexture));

	return true;
}

DXTexture* DXTextureManager::getTexture(Texture_Key _key)
{
	auto it = m_TextureList.find(_key);
	if (it != m_TextureList.end())
	{
		return it->second;
	}
	return nullptr;
}


bool DXTextureManager::initialize()
{
	Load(Texture_Key::Player, L"../../resource/0.bmp");
	Load(Texture_Key::Npc, L"../../resource/1.bmp");
	Load(Texture_Key::Obstacle, L"../../resource/2.bmp");

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
			delete it.second;
		}
	}

	return true;
}