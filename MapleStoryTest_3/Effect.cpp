#include "Effect.hpp"

Effect::Effect()
{

}

Effect::Effect(const Rect2f& _rect)
{
	shape = _rect;
}

Effect::~Effect()
{

}

bool Effect::Load(std::wstring _path)
{
	std::filesystem::path path(_path);
	for (auto& file : std::filesystem::directory_iterator(path))
	{
		//std::wstring filename = file.path().filename();
		std::wstring filepath = file.path();

		if (file.path().extension() == L"")
		{
            return false;
		}
		else
		{
			if (DXTextureManager::getInstance()->Load(filepath))
			{
				textureKeyList.push_back(filepath);
			}
		}
	}

	return true;
}

bool Effect::initialize()
{
    state = 0;
    beforeTime = 0.0f;
    timeCounter = 0.0f;
    //effectTime = 0.0f;
    frameTime = 0.0f;
    isEnd = false;
    lifeTime = 0.33f;
    totalTime = 0.0f;

    frameTime = lifeTime / textureKeyList.size();

	return true;
}

bool Effect::frame() 
{
    float currentTime = Timer::getInstance()->getPlayTime();
    float secondPerFrame = currentTime - beforeTime;
    timeCounter += secondPerFrame;
    totalTime += secondPerFrame;

    if (isEnd)
    {
        return true;
    }

    if (timeCounter >= frameTime)
    {
        timeCounter = 0.0f;

        std::wstring strTime = L"Effect[" + std::to_wstring(state) + L"] Time: " + std::to_wstring(frameTime) + L"\n";
        OutputDebugString(strTime.c_str());

        if (state < textureKeyList.size() - 1)
        {
            state++;
        }
        else
        {
            state = 0;

            if (totalTime >= lifeTime)
            {
                isEnd = true;
            }

            return true;
        }

        pShader->setTexture(DXTextureManager::getInstance()->getTexture(textureKeyList[state]));
    }

    beforeTime = currentTime;

    return true;
}

bool Effect::render()
{
    object2D<float>::render();

    DrawBorder(hitbox, BORDER_COLOR_GREEN);

	return true;
}

bool Effect::release()
{
	return true;
}
