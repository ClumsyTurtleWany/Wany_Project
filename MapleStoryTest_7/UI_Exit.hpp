#pragma once
#include <filesystem>
#include <fstream>
#include "UI_Button.hpp"

#define EXIT_DIR L"../resource/MapleStory/UI/Exit/"
#define BTN_YSE_DIR L"../resource/MapleStory/UI/Exit/btn/yes/"
#define BTN_NO_DIR L"../resource/MapleStory/UI/Exit/btn/no/"

class UI_Exit : public UserInterface
{
public:
	UI_Button* Btn_Yes = nullptr;
	UI_Button* Btn_No = nullptr;

	int initLevel = 0;
	float initExpRatio = 0.0f;

public:
	UI_Exit();
	UI_Exit(UI_Exit* _src);
	UI_Exit(const Rect2f& _rect);
	virtual ~UI_Exit();

public:
	virtual bool Load(std::wstring _path);

	bool renderTime();
	bool renderLevel();

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;

};