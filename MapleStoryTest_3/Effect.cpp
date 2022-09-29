#include "Effect.hpp"

Effect::Effect()
{

}

Effect::Effect(Effect* _src)
{
    lifeTime = _src->lifeTime;
    textureKeyList.assign(_src->textureKeyList.begin(), _src->textureKeyList.end());
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
        std::wstring filepath = file.path();
		std::wstring filename = file.path().filename();
        std::wstring fileExtension = file.path().extension();

		if (fileExtension == L"")
		{
            return false;
		}
        else if (fileExtension == L".txt")
        {
            if (filename == L"info.txt")
            {
                LoadInfo(filepath);
            }
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

bool Effect::LoadInfo(std::wstring _path)
{
	std::fstream file(_path);
	if (!file.is_open())
	{
		return false;
	}
	else
	{
		int cnt = 0;
		while (!file.eof())
		{
			std::string dataName;
			std::getline(file, dataName, '=');
			if (dataName == "lifeTime")
			{
				std::string lineData;
				std::getline(file, lineData, '\n');
				lifeTime = std::stof(lineData);
			}
		}
		file.close();
		return true;
	}
}

void Effect::setPos(Vector2f _pos)
{
    pos = _pos;
}

bool Effect::initialize()
{
    state = 0;
    beforeTime = 0.0f;
    timeCounter = 0.0f;
    frameTime = 0.0f;
    isEnd = false;
    if (lifeTime <= 0.0f)
    {
        lifeTime = 1.0f;
    }
    totalTime = 0.0f;

    frameTime = lifeTime / textureKeyList.size();

    this->createShader(ShaderType::Texture);

    if (!textureKeyList.empty())
    {
        pShader->setTexture(DXTextureManager::getInstance()->getTexture(textureKeyList[state]));
        shape = Rect2f(0, 0, pShader->getTextureWidth(), pShader->getTextureHeight());
        moveCenterTo(pos);
    }

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
        shape = Rect2f(0, 0, pShader->getTextureWidth(), pShader->getTextureHeight());
        moveCenterTo(pos);
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
