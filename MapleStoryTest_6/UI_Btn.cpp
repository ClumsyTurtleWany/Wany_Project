#include "UI_Btn.hpp"
#include "DXTextureManager.hpp"
#include "UIManager.hpp"

UI_Btn::UI_Btn()
{
}

UI_Btn::UI_Btn(UI_Btn* _src)
{
	textureKeyMap.insert(_src->textureKeyMap.begin(), _src->textureKeyMap.end());
	infoList.assign(_src->infoList.begin(), _src->infoList.end());
}

UI_Btn::UI_Btn(const Rect2f& _rect)
{
}

UI_Btn::~UI_Btn()
{
}

bool UI_Btn::Load(std::wstring _path)
{
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filepath = file.path();
		std::wstring filename = file.path().filename();
		std::wstring fileExtension = file.path().extension();
		size_t extensionIdx = filename.find_last_of(L".");
		std::wstring key = filename.substr(0, extensionIdx);

		if (fileExtension == L"")
		{
			return false;
		}
		else
		{
			if (DXTextureManager::getInstance()->Load(filepath))
			{
				textureKeyMap.insert(std::make_pair(key, filepath));
			}
		}
	}

	return true;
}

bool UI_Btn::initialize()
{
	UserInterface::initialize();
	UserInterface* pUi = UIManager::getInstance()->getUI(L"Exit");
	textureKeyMap.insert(pUi->textureKeyMap.begin(), pUi->textureKeyMap.end());
	infoList.assign(pUi->infoList.begin(), pUi->infoList.end());

	return true;
}

bool UI_Btn::frame()
{
	POINT mousePt = Input::getInstance()->m_ptPos;


	for (auto it : childList)
	{
		it->frame();
	}

	return true;
}

bool UI_Btn::render()
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
				if (it.textureKey == L"exp")
				{
					float ratio = static_cast<float>(user->info.currentExp) / static_cast<float>(user->info.requiredExp);
					width *= ratio;
				}
				Rect2f drawRect(pos.x + it.pos.x, pos.y + it.pos.y, width, height);
				this->shape = drawRect;
				setTexture(pTexture);

				object2D<float>::render();
			}
		}
	}

	for (auto it : childList)
	{
		it->render();
	}

	return true;
}

bool UI_Btn::release()
{
	return false;
}
