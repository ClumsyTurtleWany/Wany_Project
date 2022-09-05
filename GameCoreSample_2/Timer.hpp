#pragma once
#include "Define.hpp"

// 교재 7강 Timer 참고할 것 나중에 HRT로 바꿀 것.
class Timer : public Singleton<Timer>
{
public:
	float	gameTime = 0.0f;
	float	secondPerFrame = 0.0f;
	float	fps = 0.0f;

private:
	float	beforeTime = 0.0f;
	float	fpsTimer = 0.0f;
	UINT	fpsCounter = 0;


public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();

public:
	float getPlayTime();
	float getDeltaTime();
	float getFPS();

	
};

bool Timer::initialize()
{
	gameTime = 0.0f;
	secondPerFrame = 0.0f;
	fps = 0;
	fpsCounter = 0;
	fpsTimer = 0.0f;

	beforeTime = timeGetTime();
	return true;
}

bool Timer::frame()
{
	float currentTime = timeGetTime();
	secondPerFrame = (currentTime - beforeTime) / 1000.0f;
	gameTime += secondPerFrame;
	fpsCounter++;
	beforeTime = currentTime;

	fpsTimer += secondPerFrame;
	if (fpsTimer >= 1.0f)
	{
		fps = fpsCounter;
		fpsTimer -= 1.0f;
		fpsCounter = 0;
	}
	return true;
}

bool Timer::render()
{
	std::wstring strTime = std::to_wstring(gameTime);
	std::wstring strFPS = std::to_wstring(fps);
	strTime = strTime + L" : " + strFPS +  L"\n";
	OutputDebugStringW(strTime.c_str());

	return true;
}

bool Timer::release()
{

	return true;
}

float Timer::getPlayTime()
{
	return gameTime;
}

float Timer::getDeltaTime()
{
	return secondPerFrame;
}

float Timer::getFPS()
{
	return fps;
}