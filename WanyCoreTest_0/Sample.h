#pragma once
//#include "WindowUI.hpp"
#include "core/DXDevice.hpp"

class Sample : public DXDevice
{
public:
	bool initialize() override;
	bool frame() override;
	bool render() override;
	bool release() override;
	bool run() override;
};