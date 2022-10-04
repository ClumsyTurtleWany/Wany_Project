#include "DamageEffect.hpp"

DamageEffect::DamageEffect()
{

}

DamageEffect::DamageEffect(DamageEffect* _src)
{
    lifeTime = _src->lifeTime;
    textureKeyMap.insert(_src->textureKeyMap.begin(), _src->textureKeyMap.end());
}

DamageEffect::DamageEffect(const Rect2f& _rect)
{
    shape = _rect;
}

DamageEffect::~DamageEffect()
{

}

bool DamageEffect::Load(std::wstring _path)
{
    std::filesystem::path path(_path);
    for (auto& file : std::filesystem::directory_iterator(path))
    {
        std::wstring filepath = file.path(); 
        std::wstring fileExtension = file.path().extension();
        std::wstring filename = file.path().filename();
        size_t extensionIdx = filename.find_last_of(L".");
        std::wstring key = filename.substr(0, extensionIdx);

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
                textureKeyMap.insert(std::make_pair(key, filepath));
            }
        }
    }

    return true;
}

bool DamageEffect::LoadInfo(std::wstring _path)
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

void DamageEffect::setPos(Vector2f _pos)
{
    pos = _pos;
}

void DamageEffect::setDamage(int _damage)
{
    damage = _damage;
}

bool DamageEffect::initialize()
{
    state = 0;
    beforeTime = Timer::getInstance()->getPlayTime();
    timeCounter = 0.0f;
    frameTime = 0.1f;
    isEnd = false;
    if (lifeTime <= 0.0f)
    {
        lifeTime = 2.0f;
    }
    lifeTime = 2.0f;
    totalTime = 0.0f;

    this->createShader(ShaderType::Texture);

    this->force.y = -50.0f;

    //if (!textureKeyList.empty())
    //{
    //    pShader->setTexture(DXTextureManager::getInstance()->getTexture(textureKeyList[state]));
    //    shape = Rect2f(0, 0, pShader->getTextureWidth(), pShader->getTextureHeight());
    //    moveCenterTo(pos);
    //}

    return true;
}

bool DamageEffect::frame()
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
        float decreaseAlpha = 1.0f / (lifeTime / timeCounter);
        timeCounter = 0.0f;

        std::wstring strTime = L"DamageEffect[" + std::to_wstring(state) + L"] Time: " + std::to_wstring(frameTime) + L"\n";
        OutputDebugString(strTime.c_str());

        pos.y -= 10;

        this->setAlpha(alphaBlendVal);
        alphaBlendVal -= decreaseAlpha;
    }

    if (totalTime >= lifeTime)
    {
        isEnd = true;
    }

    beforeTime = currentTime;

    return true;
}

bool DamageEffect::render()
{
    Vector2f numberPos = pos;
    std::wstring wstrDamage = std::to_wstring(damage);
    for (size_t idx = 0; idx < wstrDamage.size(); idx++)
    {
        std::wstring charDamage;
        charDamage = wstrDamage.at(idx);

        auto it = textureKeyMap.find(charDamage);
        if (it != textureKeyMap.end())
        {
            DXTexture* pTexture = DXTextureManager::getInstance()->getTexture(it->second);
            setTexture(pTexture);
            float aspectRatio = 1.5f;
            float width = pTexture->getWidth() * aspectRatio;
            float height = pTexture->getHeight() * aspectRatio;
            Rect2f numberRect(0, 0, width, height);
            this->shape = numberRect;
            moveCenterTo(numberPos);

            numberPos.x += width;

            object2D<float>::render();
        }
    }
    //object2D<float>::render();

    //DrawBorder(hitbox, BORDER_COLOR_GREEN);

    return true;
}

bool DamageEffect::release()
{
    return true;
}
