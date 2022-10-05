#pragma once
#include <filesystem>
#include <fstream>
#include "UserInterface.hpp"
#include "Input.hpp"
#include <functional>

class UI_Button : public UserInterface
{
public:
	enum class BtnState
	{
		Normal,
		Disable,
		MouseOver,
		Pressed,
		None,
	};

public:
	UI_Button();
	UI_Button(UI_Button* _src);
	UI_Button(const Rect2f& _rect);
	virtual ~UI_Button();

private:
	BtnState state = BtnState::Normal;
	bool pressed = false;
	std::map<BtnState, std::wstring> BtnTextureMap;
	std::function<void()> callbackFunction;

private:
	bool setStateTexture(BtnState _state);

public:
	virtual bool Load(std::wstring _path) override;
	virtual bool isPressed();
	virtual void setCallbackFunction(std::function<void()> _callback);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;

};