#pragma once
#include "DXDevice.hpp"
#include "Timer.hpp"
#include "Input.hpp"
#include "DXWriter.hpp"
#include "DXSamplerState.hpp"

class GameCore : public DXDevice
{

public:
	virtual bool initialize() { return true; };
	virtual bool frame() { return true; };
	virtual bool render() { return true; };
	virtual bool release() { return true; };

private:
	bool CoreInitialize();
	bool CoreFrame();
	bool CoreRender();
	bool CoreRelease();
	bool PreRender();
	bool PostRender();
	

public:
	bool run();
};