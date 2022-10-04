#pragma once
#include <filesystem>
#include <fstream>
#include "UserInterface.hpp"

class UI_Exit : public UserInterface
{
public:
	UI_Exit();
	UI_Exit(UI_Exit* _src);
	UI_Exit(const Rect2f& _rect);
	virtual ~UI_Exit();

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;

};