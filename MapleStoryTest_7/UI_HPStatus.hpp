#pragma once
#include <filesystem>
#include <fstream>
#include "Player.hpp"
#include "UserInterface.hpp"

class UI_HPStatus : public UserInterface
{
public:
	float aspectRatio = 1.2f;

public:
	UI_HPStatus();
	UI_HPStatus(UI_HPStatus* _src);
	UI_HPStatus(const Rect2f& _rect);
	virtual ~UI_HPStatus();

public:
	bool renderLevel();
	bool renderHP();
	bool renderMP();

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;

};