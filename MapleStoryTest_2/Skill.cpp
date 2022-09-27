#include "Skill.hpp"

Skill::Skill()
{
}

Skill::Skill(const Rect2f& _rect)
{
	shape = _rect;
}

Skill::~Skill()
{

}

void Skill::setCamera(Camera* _camera)
{
	renderCamera = _camera;
}

bool Skill::initialize()
{
    state = 0;
    beforeTime = 0.0f;
    timeCounter = 0.0f;
    //effectTime = 0.0f;
    frameTime = 0.0f;
    coolTime = 0.33f;
    isEnd = false;
    lifeTime = 0.33f;
    totalTime = 0.0f;

    isCancel = false;

    frameTime = lifeTime / textureKeyList.size();


    float x = 0.0f;
    float y = 0.0f;
    float width = 504;
    float height = 332;
    float offset_x = 100.0f;

    float hitboxOffset_x = 10.0f;
    float hitboxOffset_y = 10.0f;
    float hitbox_x = 0.0f;
    float hitbox_y = 0.0f;
    float hitbox_width = 0.0f;
    float hitbox_height = 0.0f;
    if (user->currentDirection == Player::Direction::Left)
    {
        x = user->shape.cx() - width + offset_x;
        y = user->shape.RB.y - height; //user->shape.cy() - height; //user->shape.RB.y - height; 

        hitbox_x = x + hitboxOffset_x;
        hitbox_y = y + hitboxOffset_y;
        hitbox_width = width - (hitboxOffset_x * 2.0f);
        hitbox_height = height - (hitboxOffset_y * 2.0f);
    }
    else
    {
        x = user->shape.cx() - offset_x;
        y = user->shape.RB.y - height; //user->shape.cy() - height; //user->shape.RB.y - height;

        hitbox_x = x + hitboxOffset_x;
        hitbox_y = y + hitboxOffset_y;
        hitbox_width = width - (hitboxOffset_x * 2.0f);
        hitbox_height = height - (hitboxOffset_y * 2.0f);
    }

    this->hitbox = Rect2f(hitbox_x, hitbox_y, hitbox_width, hitbox_height);
    this->mapWidth = user->mapWidth;
    this->mapHeight = user->mapHeight;

    moveTo(user->shape.center());

    if (!textureKeyList.empty())
    {
        DXTexture* texture = DXTextureManager::getInstance()->getTexture(textureKeyList[state]);
        this->shape = Rect2f(x, y, texture->getWidth(), texture->getHeight());
    }

    this->setCamera(user->renderCamera);
    

    beforeTime = Timer::getInstance()->getPlayTime();
    
	return this->createShader(ShaderType::Texture);
}

bool Skill::frame()
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
            moveTo(user->shape.center());

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
                //if (totalTime >= coolTime)
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
        if (linkedSkill != nullptr)
        {
            linkedSkill->user = user;
            linkedSkill->frame();
        }
        else
        {
            isEnd = true;
        }
    }

    beforeTime = currentTime;

	return true;
}

bool Skill::render()
{
	object2D<float>::render();

    DrawBorder(hitbox, BORDER_COLOR_GREEN);

	return true;
}

bool Skill::release()
{
	return true;
}