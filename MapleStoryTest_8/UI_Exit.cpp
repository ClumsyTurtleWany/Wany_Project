#include "UI_Exit.hpp"
#include "DXTextureManager.hpp"
#include "UIManager.hpp"
#include "UI_Button.hpp"
#include "Timer.hpp"

UI_Exit::UI_Exit()
{
}

UI_Exit::UI_Exit(UI_Exit* _src)
{
}

UI_Exit::UI_Exit(const Rect2f& _rect)
{
}

UI_Exit::~UI_Exit()
{
}

bool UI_Exit::Load(std::wstring _path)
{
	return false;
}

bool UI_Exit::initialize()
{
	UserInterface::initialize();
	UserInterface* pUi = UIManager::getInstance()->getUI(L"Exit");
	copy(pUi);

	Btn_Yes = new UI_Button;
	Btn_Yes->Load(BTN_YSE_DIR);
	Btn_Yes->initialize();
	Btn_Yes->setPos(Vector2f(pos.x + 70.0f, pos.y + 150.0f));

	Btn_No = new UI_Button;
	Btn_No->Load(BTN_NO_DIR);
	Btn_No->initialize();
	Btn_No->setPos(Vector2f(pos.x + 200.0f, pos.y + 150.0f));

	if (user != nullptr)
	{
		initLevel = user->info.level;
		initExpRatio = (static_cast<float>(user->info.currentExp) / static_cast<float>(user->info.requiredExp)) * 100.0f;
	}

	return true;
}

bool UI_Exit::frame()
{
	/*for (size_t idx = 0; idx < childList.size(); idx++)
	{
		childList[idx]->frame();
		if (idx == 0)
		{
			UI_Button* pButton = dynamic_cast<UI_Button*>(childList[idx]);
			if (pButton->isPressed())
			{
				ClickEvent_Yes();
			}
		}
		else
		{
			UI_Button* pButton = dynamic_cast<UI_Button*>(childList[idx]);
			if (pButton->isPressed())
			{
				ClickEvent_No();
			}
		}
		
	}*/
	Btn_Yes->setPos(Vector2f(pos.x + 70.0f, pos.y + 150.0f));
	Btn_Yes->frame();
	if (Btn_Yes->isPressed())
	{
		PostQuitMessage(0);
	}

	Btn_No->setPos(Vector2f(pos.x + 200.0f, pos.y + 150.0f));
	Btn_No->frame();
	if (Btn_No->isPressed())
	{
		isClose = true;
	}

	return true;
}

bool UI_Exit::renderTime()
{
	int playTime = static_cast<int>(Timer::getInstance()->getPlayTime());
	int minute = (playTime / 60) % 60;
	int hour = (playTime / 60) / 60;

	std::map<std::wstring, std::wstring>* pFontMap;
	auto it = fontMapList.find(L"time");
	if (it != fontMapList.end())
	{
		pFontMap = &it->second;
	}
	else
	{
		return false;
	}

	std::wstring wstrTime;
	if (hour == 0)
	{
		wstrTime += L"00";
	}
	else if (hour < 10)
	{
		wstrTime += L"0";
		wstrTime += std::to_wstring(hour);
	}
	else
	{
		wstrTime += std::to_wstring(hour);
	}
	wstrTime += L":";

	if (minute == 0)
	{
		wstrTime += L"00";
	}
	else if (minute < 10)
	{
		wstrTime += L"0";
		wstrTime += std::to_wstring(minute);
	}
	else
	{
		wstrTime += std::to_wstring(minute);
	}

	Vector2f tempPos = pos;
	tempPos.x += 25;
	tempPos.y += 105;
	for (size_t idx = 0; idx < wstrTime.size(); idx++)
	{
		std::wstring charKey;
		charKey = wstrTime.at(idx);
		if (charKey == L":")
		{
			charKey = L"colon";
		}

		auto iterKey = pFontMap->find(charKey);
		if (iterKey != pFontMap->end())
		{
			DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(iterKey->second);
			if (pTexture != nullptr)
			{
				setTexture(pTexture);
				float width = pTexture->getWidth();
				float height = pTexture->getHeight();
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

bool UI_Exit::renderLevel()
{
	std::map<std::wstring, std::wstring>* pFontMap;
	auto it = fontMapList.find(L"level");
	if (it != fontMapList.end())
	{
		pFontMap = &it->second;
	}
	else
	{
		return false;
	}

	std::wstring wstrInitLevel = std::to_wstring(initLevel);

	Vector2f tempPos = pos;
	tempPos.x += 175;
	tempPos.y += 103;
	for (size_t idx = 0; idx < wstrInitLevel.size(); idx++)
	{
		std::wstring charKey;
		charKey = wstrInitLevel.at(idx);

		auto iterKey = pFontMap->find(charKey);
		if (iterKey != pFontMap->end())
		{
			DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(iterKey->second);
			if (pTexture != nullptr)
			{
				setTexture(pTexture);
				float width = pTexture->getWidth();
				float height = pTexture->getHeight();
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

	std::wstring currentLevel = std::to_wstring(user->info.level);
	tempPos = pos;
	tempPos.x += 275;
	tempPos.y += 103;
	for (size_t idx = 0; idx < currentLevel.size(); idx++)
	{
		std::wstring charKey;
		charKey = currentLevel.at(idx);

		auto iterKey = pFontMap->find(charKey);
		if (iterKey != pFontMap->end())
		{
			DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(iterKey->second);
			if (pTexture != nullptr)
			{
				setTexture(pTexture);
				float width = pTexture->getWidth();
				float height = pTexture->getHeight();
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

bool UI_Exit::render()
{
	for (auto it : infoList)
	{
		auto iter = textureKeyMap.find(it.textureKey);
		if (iter != textureKeyMap.end())
		{
			DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(iter->second);
			if (pTexture != nullptr)
			{
				float width = pTexture->getWidth();
				float height = pTexture->getHeight();
				Rect2f drawRect(pos.x + it.pos.x, pos.y + it.pos.y, width, height);
				this->shape = drawRect;
				setTexture(pTexture);

				object2D<float>::render();
			}
		}
	}

	renderTime();
	renderLevel();

	/*for (auto it : childList)
	{
		it->render();
	}*/

	Btn_Yes->render();
	Btn_No->render();

	return true;
}

bool UI_Exit::release()
{
	return false;
}
