#pragma once
#include "DXDevice.hpp"

class Sample : public DXDevice
{
public:
	bool initialize();
	bool frame();
	bool render();
	bool release();
};

bool Sample::initialize()
{
	DXDevice::initialize();
	return true;
}

bool Sample::frame()
{
	DXDevice::frame();
	return true;
}

bool Sample::render()
{
	DXDevice::render();
	return true;
}

bool Sample::release()
{
	DXDevice::release();
	return true;
}