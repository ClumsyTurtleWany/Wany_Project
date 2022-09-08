#include "Timer.hpp"

bool Timer::initialize()
{
	gameTime = 0.0f;
	secondPerFrame = 0.0f;
	fps = 0;
	fpsCounter = 0;
	fpsTimer = 0.0f;

	beforeTime = static_cast<float>(timeGetTime());
	return true;
}

bool Timer::frame()
{
	float currentTime = static_cast<float>(timeGetTime());
	secondPerFrame = (currentTime - beforeTime) / 1000.0f;
	gameTime += secondPerFrame;
	fpsCounter++;
	beforeTime = currentTime;

	fpsTimer += secondPerFrame;
	if (fpsTimer >= 1.0f)
	{
		fps = static_cast<float>(fpsCounter);
		fpsTimer -= 1.0f;
		fpsCounter = 0;
	}
	return true;
}

bool Timer::render()
{
	std::wstring strTime = std::to_wstring(gameTime);
	std::wstring strFPS = std::to_wstring(fps);
	strTime = strTime + L" : " + strFPS + L"\n";
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