#include "UI_Exp.hpp"
#include "DXTextureManager.hpp"
#include "UIManager.hpp"

UI_Exp::UI_Exp()
{
}

UI_Exp::UI_Exp(UI_Exp* _src)
{
	textureKeyMap.insert(_src->textureKeyMap.begin(), _src->textureKeyMap.end());
	infoList.assign(_src->infoList.begin(), _src->infoList.end());
}

UI_Exp::UI_Exp(const Rect2f& _rect)
{
}

UI_Exp::~UI_Exp()
{
}

bool UI_Exp::initialize()
{
	UserInterface::initialize();
	UserInterface* pUi = UIManager::getInstance()->getUI(L"Exp_bar");
	textureKeyMap.insert(pUi->textureKeyMap.begin(), pUi->textureKeyMap.end());
	infoList.assign(pUi->infoList.begin(), pUi->infoList.end());

	return true;
}

bool UI_Exp::frame()
{
	for (auto it : childList)
	{
		it->frame();
	}

	return true;
}

bool UI_Exp::render()
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

bool UI_Exp::release()
{
	return false;
}
