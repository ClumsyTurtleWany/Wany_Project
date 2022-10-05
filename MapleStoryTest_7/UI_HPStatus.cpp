#include "UI_HPStatus.hpp"
#include "DXTextureManager.hpp"
#include "UIManager.hpp"

UI_HPStatus::UI_HPStatus()
{
}

UI_HPStatus::UI_HPStatus(UI_HPStatus* _src)
{
	textureKeyMap.insert(_src->textureKeyMap.begin(), _src->textureKeyMap.end());
	infoList.assign(_src->infoList.begin(), _src->infoList.end());
}

UI_HPStatus::UI_HPStatus(const Rect2f& _rect)
{
}

UI_HPStatus::~UI_HPStatus()
{
}

bool UI_HPStatus::renderLevel()
{
	std::map<std::wstring, std::wstring>* pFontMap;
	auto it = fontMapList.find(L"Level");
	if (it != fontMapList.end())
	{
		pFontMap = &it->second;
	}
	else
	{
		return false;
	}

	Vector2f HPbarPos;
	for (auto iter : infoList)
	{
		if (iter.textureKey == L"hp")
		{
			HPbarPos = iter.pos;
		}
	}

	Vector2f tempPos = pos;
	tempPos.x += HPbarPos.x * aspectRatio;
	tempPos.y += 8;

	auto iterLv = pFontMap->find(L"Lv");
	if (iterLv != pFontMap->end())
	{
		DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(iterLv->second);
		if (pTexture != nullptr)
		{
			setTexture(pTexture);
			float width = pTexture->getWidth() * aspectRatio;
			float height = pTexture->getHeight() * aspectRatio;
			this->shape = Rect2f(tempPos.x, tempPos.y, width, height);
			object2D<float>::render();
			tempPos.x += width;
		}
	}

	std::wstring level = std::to_wstring(user->info.level);
	for (size_t idx = 0; idx < level.size(); idx++)
	{
		std::wstring charKey;
		charKey = level.at(idx);

		auto iterKey = pFontMap->find(charKey);
		if (iterKey != pFontMap->end())
		{
			DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(iterKey->second);
			if (pTexture != nullptr)
			{
				setTexture(pTexture);
				float width = pTexture->getWidth() * aspectRatio;
				float height = pTexture->getHeight() * aspectRatio;
				this->shape = Rect2f(tempPos.x, tempPos.y, width, height);
				object2D<float>::render();
				tempPos.x += width;
			}
		}
	}
	
}

bool UI_HPStatus::renderHP()
{
	std::map<std::wstring, std::wstring>* pFontMap;
	auto it = fontMapList.find(L"HP&MP");
	if (it != fontMapList.end())
	{
		pFontMap = &it->second;
	}
	else
	{
		return false;
	}

	Vector2f HPbarPos;
	for (auto iter : infoList)
	{
		if (iter.textureKey == L"hp")
		{
			HPbarPos = iter.pos;
		}
	}
	
	std::wstring strForPos = std::to_wstring(user->info.maxHP) + L"/" + std::to_wstring(user->info.maxHP);
	std::wstring HP = std::to_wstring(user->info.currentHP) + L"/" + std::to_wstring(user->info.maxHP);
	Vector2f tempPos = pos + HPbarPos * aspectRatio;
	tempPos.x += 128 - (strForPos.size() * 8);
	tempPos.y += 2;
	
	for (size_t idx = 0; idx < HP.size(); idx++)
	{
		std::wstring charKey;
		charKey = HP.at(idx);
		if (charKey == L"/")
		{
			charKey = L"Slash";
		}

		auto iterKey = pFontMap->find(charKey);
		if (iterKey != pFontMap->end())
		{
			DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(iterKey->second);
			if (pTexture != nullptr)
			{
				setTexture(pTexture);
				float width = pTexture->getWidth() * aspectRatio;
				float height = pTexture->getHeight() * aspectRatio;
				this->shape = Rect2f(tempPos.x, tempPos.y, width, height);
				object2D<float>::render();
				tempPos.x += width;
			}
			else
			{
				tempPos.x += 1;
			}
		}
		else
		{
			continue;
		}
	}
	return true;
}

bool UI_HPStatus::renderMP()
{
	std::map<std::wstring, std::wstring>* pFontMap;
	auto it = fontMapList.find(L"HP&MP");
	if (it != fontMapList.end())
	{
		pFontMap = &it->second;
	}
	else
	{
		return false;
	}

	Vector2f HPbarPos;
	for (auto iter : infoList)
	{
		if (iter.textureKey == L"mp")
		{
			HPbarPos = iter.pos;
		}
	}

	std::wstring strForPos = std::to_wstring(user->info.maxMP) + L"/" + std::to_wstring(user->info.maxMP);
	std::wstring MP = std::to_wstring(user->info.currentMP) + L"/" + std::to_wstring(user->info.maxMP);
	Vector2f tempPos = pos + HPbarPos * aspectRatio;
	tempPos.x += 128 - (MP.size() * 8);
	tempPos.y += 2;

	for (size_t idx = 0; idx < MP.size(); idx++)
	{
		std::wstring charKey;
		charKey = MP.at(idx);
		if (charKey == L"/")
		{
			charKey = L"Slash";
		}

		auto iterKey = pFontMap->find(charKey);
		if (iterKey != pFontMap->end())
		{
			DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(iterKey->second);
			if (pTexture != nullptr)
			{
				setTexture(pTexture);
				float width = pTexture->getWidth() * aspectRatio;
				float height = pTexture->getHeight() * aspectRatio;
				this->shape = Rect2f(tempPos.x, tempPos.y, width, height);
				object2D<float>::render();
				tempPos.x += width;
			}
			else
			{
				tempPos.x += 1;
			}
		}
		else
		{
			continue;
		}
	}
	return true;
}

bool UI_HPStatus::initialize()
{
	UserInterface::initialize();
	UserInterface* pUi = UIManager::getInstance()->getUI(L"HP_bar");
	textureKeyMap.insert(pUi->textureKeyMap.begin(), pUi->textureKeyMap.end());
	infoList.assign(pUi->infoList.begin(), pUi->infoList.end());
	fontMapList.insert(pUi->fontMapList.begin(), pUi->fontMapList.end());

	return true;
}

bool UI_HPStatus::frame()
{
	for (auto it : childList)
	{
		it->frame();
	}

	return true;
}

bool UI_HPStatus::render()
{
	for (auto it : infoList)
	{
		auto iter = textureKeyMap.find(it.textureKey);
		if (iter != textureKeyMap.end())
		{
			DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(iter->second);
			if (pTexture != nullptr)
			{
				float width = pTexture->getWidth() * aspectRatio;
				float height = pTexture->getHeight() * aspectRatio;
				if (it.textureKey == L"hp")
				{
					float ratio = static_cast<float>(user->info.currentHP) / static_cast<float>(user->info.maxHP);
					width *= ratio;
				}
				else if (it.textureKey == L"mp")
				{
					float ratio = static_cast<float>(user->info.currentMP) / static_cast<float>(user->info.maxMP);
					width *= ratio;
				}
				float x = pos.x + it.pos.x * aspectRatio;
				float y = pos.y + it.pos.y * aspectRatio;
				Rect2f drawRect(x, y, width, height);
				this->shape = drawRect;
				setTexture(pTexture);

				object2D<float>::render();

				
			}
		}
	}

	bool rst = renderLevel();
	rst = renderHP();
	rst = renderMP();

	for (auto it : childList)
	{
		it->render();
	}

	return true;
}

bool UI_HPStatus::release()
{
	return false;
}
