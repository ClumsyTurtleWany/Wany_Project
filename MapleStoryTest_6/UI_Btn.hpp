#pragma once
#include <filesystem>
#include <fstream>
#include "UserInterface.hpp"
#include "Input.hpp"

class UI_Btn : public UserInterface
{
public:
	enum class State
	{
		normal,
		disable,
		mouseOver,
		pressed,
	};

public:
	UI_Btn();
	UI_Btn(UI_Btn* _src);
	UI_Btn(const Rect2f& _rect);
	virtual ~UI_Btn();

private:
	State state = State::normal;
	bool pressed = false;

public:
	bool isPressed();

public:
	virtual bool Load(std::wstring _path) override;

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;

};