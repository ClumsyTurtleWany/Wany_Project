#pragma once
#include "DXTexture.hpp"

class DXTextureManager : public Singleton<DXTextureManager>
{
private:
	friend class Singleton<DXTextureManager>;

	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

	std::map<Texture_Key, DXTexture*> m_TextureList;
	std::map<Texture_Key, DXTexture*> m_TextureMaskList;
	std::map<Sprite_Key, std::vector<Rect_<float>>> m_SpriteRectList;

private:
	DXTextureManager() {};
	~DXTextureManager() { release(); };

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
	bool Load(Texture_Key _key, std::wstring _filename);
	bool LoadMask(Texture_Key _key, std::wstring _filename);
	DXTexture* getTexture(Texture_Key _key);
	DXTexture* getTextureMask(Texture_Key _key);
	std::vector<Rect_<float>>& getSpriteList(Sprite_Key _key);

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

bool DXTextureManager::LoadMask(Texture_Key _key, std::wstring _filename)
{
	DXTexture* newTexture = new DXTexture;
	newTexture->setDevice(m_pd3dDevice, m_pImmediateContext);
	HRESULT rst = newTexture->Load(_filename);
	if (FAILED(rst))
	{
		return false;
	}

	m_TextureMaskList.insert(std::make_pair(_key, newTexture));

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

DXTexture* DXTextureManager::getTextureMask(Texture_Key _key)
{
	auto it = m_TextureMaskList.find(_key);
	if (it != m_TextureMaskList.end())
	{
		return it->second;
	}
	return nullptr;
}

std::vector<Rect_<float>>& DXTextureManager::getSpriteList(Sprite_Key _key)
{
	auto it = m_SpriteRectList.find(_key);
	if (it != m_SpriteRectList.end())
	{
		return it->second;
	}
	return std::vector<Rect_<float>>();
}


bool DXTextureManager::initialize()
{
	//Load(Texture_Key::Player, L"../../resource/0.bmp");
	//Load(Texture_Key::Npc, L"../../resource/1.bmp");
	//Load(Texture_Key::Obstacle, L"../../resource/2.bmp");
	Load(Texture_Key::Charater, L"../../resource/bitmap1.bmp");
	LoadMask(Texture_Key::Charater, L"../../resource/bitmap2.bmp");

	std::vector<Rect_<float>> PlayerSprite;
	PlayerSprite.push_back(Rect_<float>(1, 1, 26, 60));
	PlayerSprite.push_back(Rect_<float>(28, 1, 26, 60));
	PlayerSprite.push_back(Rect_<float>(55, 1, 34, 60));
	PlayerSprite.push_back(Rect_<float>(90, 1, 42, 60));
	PlayerSprite.push_back(Rect_<float>(133, 1, 42, 60));
	PlayerSprite.push_back(Rect_<float>(176, 1, 34, 60));
	PlayerSprite.push_back(Rect_<float>(211, 1, 26, 60));
	PlayerSprite.push_back(Rect_<float>(238, 1, 26, 60));
	m_SpriteRectList.insert(std::make_pair(Sprite_Key::Player, PlayerSprite));


	Load(Texture_Key::World, L"../../resource/KGCABK.bmp");

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

	if (!m_TextureMaskList.empty())
	{
		for (auto it : m_TextureMaskList)
		{
			delete it.second;
		}
	}

	return true;
}