#pragma once
#include <filesystem>
#include <fstream>
#include "Player.hpp"
#include "UserInterface.hpp"

class UI_Exp : public UserInterface
{
public:
	UI_Exp();
	UI_Exp(UI_Exp* _src);
	UI_Exp(const Rect2f& _rect);
	virtual ~UI_Exp();

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;

};