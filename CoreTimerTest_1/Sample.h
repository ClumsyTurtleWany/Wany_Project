#pragma once
#include "GameCore.hpp"

class Sample : public GameCore
{
public:
	bool initialize() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};