#include "Skill_Installation.hpp"

bool Skill_Installation::frame()
{
    float currentTime = Timer::getInstance()->getPlayTime();
    float secondPerFrame = currentTime - beforeTime;
    timeCounter += secondPerFrame;
    totalTime += secondPerFrame;

    if (!isEnd)
    {

        if (timeCounter >= frameTime)
        {
            timeCounter = 0.0f;

            std::wstring strTime = L"Skill[" + std::to_wstring(state) + L"] Time: " + std::to_wstring(frameTime) + L"\n";
            OutputDebugString(strTime.c_str());

            if (state == 0)
            {
                std::vector<object2D<float>*> collisionList;
                std::vector<Rect2f> collisionRectList;
                user->currentMap->Collision(this, &collisionList, &collisionRectList);
                for (auto it : collisionRectList)
                {
                    DrawBorder(it, BORDER_COLOR_BLUE);
                }
            }

            if (state < textureKeyList.size() - 1)
            {
                state++;
            }
            else
            {
                state = 0;
                user->currentMap->updateDynamicObject();

                if (totalTime >= lifeTime)
                {
                    isEnd = true;
                }

                return true;
            }

            pShader->setTexture(DXTextureManager::getInstance()->getTexture(textureKeyList[state]));
            //setTexture(DXTextureManager::getInstance()->getTexture(textureKeyList[state]));
        }


    }
    else
    {
        /*if (linkedSkill != nullptr)
        {
            linkedSkill->user = user;
            linkedSkill->frame();
        }
        else*/
        {
            isEnd = true;
        }
    }

    beforeTime = currentTime;

    return true;
}
