#pragma once

class Timer
{
private:
	float gameTime = 0.0f;
	float elapseTime = 0.0f;
	float fps = 0.0f;
	float beforeTime = 0.0f;

	float fpsTimer = 0.0f;

	UINT fpsCounter = 0;


public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();
	
};

bool Timer::initialize()
{
	gameTime = 0.0f;
	elapseTime = 0.0f;
	fps = 0;
	fpsCounter = 0;
	fpsTimer = 0.0f;

	beforeTime = timeGetTime();
	return true;
}

bool Timer::frame()
{
	float currentTime = timeGetTime();
	elapseTime = (currentTime - beforeTime) / 1000.0f;
	gameTime += elapseTime;
	fpsCounter++;
	beforeTime = currentTime;

	fpsTimer += elapseTime;
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