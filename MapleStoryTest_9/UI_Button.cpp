#include "UI_Button.hpp"
#include "DXTextureManager.hpp"
#include "UIManager.hpp"

UI_Button::UI_Button()
{
}

UI_Button::UI_Button(UI_Button* _src)
{
	textureKeyMap.insert(_src->textureKeyMap.begin(), _src->textureKeyMap.end());
	infoList.assign(_src->infoList.begin(), _src->infoList.end());
}

UI_Button::UI_Button(const Rect2f& _rect)
{
}

UI_Button::~UI_Button()
{
}

bool UI_Button::setStateTexture(BtnState _state)
{
	auto it = BtnTextureMap.find(_state);
	if (it != BtnTextureMap.end())
	{
		DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(it->second);
		setTexture(pTexture);
		float width = pTexture->getWidth();
		float height = pTexture->getHeight();
		shape = Rect2f(pos.x, pos.y, width, height);
		return true;
	}
	else
	{
		return false;
	}
}

bool UI_Button::Load(std::wstring _path)
{
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		std::wstring filepath = file.path();
		std::wstring filename = file.path().filename();
		std::wstring fileExtension = file.path().extension();
		size_t extensionIdx = filename.find_last_of(L".");
		std::wstring wstrKey = filename.substr(0, extensionIdx);
		
		if (fileExtension == L"")
		{
			return false;
		}
		else
		{
			if (DXTextureManager::getInstance()->Load(filepath))
			{
				BtnState key = BtnState::None;
				if (wstrKey == L"normal")
				{
					key = BtnState::Normal;
				}
				else if (wstrKey == L"disable")
				{
					key = BtnState::Disable;
				}
				else if (wstrKey == L"mouseOver")
				{
					key = BtnState::MouseOver;
				}
				else if (wstrKey == L"pressed")
				{
					key = BtnState::Pressed;
				}

				BtnTextureMap.insert(std::make_pair(key, filepath));
			}
		}
	}

	return true;
}

bool UI_Button::isPressed()
{
	return pressed;
}

void UI_Button::setCallbackFunction(std::function<void()> _callback)
{
	callbackFunction = _callback;
}

bool UI_Button::initialize()
{
	UserInterface::initialize();
	state = BtnState::Normal;
	setStateTexture(state);

	return true;
}

bool UI_Button::frame()
{
	POINT mousePt = Input::getInstance()->m_ptPos;
	if (shape.PtInRect(mousePt.x, mousePt.y))
	{
		if (state == BtnState::Pressed)
		{
			KeyState keyState_Up = Input::getInstance()->getKey(VK_LBUTTON);
			if ((keyState_Up == KeyState::Up) || (keyState_Up == KeyState::Free))
			{
				pressed = true;
				if (callbackFunction != nullptr)
				{
					callbackFunction();
				}
				return true;
			}
		}
		
		KeyState keyState_Click = Input::getInstance()->getKey(VK_LBUTTON);
		if ((keyState_Click == KeyState::Down) || (keyState_Click == KeyState::Hold))
		{
			state = BtnState::Pressed;
		}
		else
		{
			state = BtnState::MouseOver;
		}
	}
	else
	{
		state = BtnState::Normal;
	}

	pressed = false;

	setStateTexture(state);

	for (auto it : childList)
	{
		it->frame();
	}

	return true;
}

bool UI_Button::render()
{
	object2D<float>::render();
	
	for (auto it : childList)
	{
		it->render();
	}

	return true;
}

bool UI_Button::release()
{
	return false;
}
