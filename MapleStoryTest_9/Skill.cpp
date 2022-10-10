#include "Skill.hpp"
#include "EffectManager.hpp"
#include "NPC.hpp"

Skill::Skill()
{
}

Skill::Skill(Skill* _src)
{
    // Effect
    lifeTime = _src->lifeTime;
    textureKeyList.assign(_src->textureKeyList.begin(), _src->textureKeyList.end());

    // Skill
    skillName = _src->skillName;
    skillType = _src->skillType;
    coolTime = _src->coolTime;
    damageList.assign(_src->damageList.begin(), _src->damageList.end());
    user = _src->user;
    offset = _src->offset;
    offset_hitbox = _src->offset_hitbox;
    hitState = _src->hitState;
    requiredMP = _src->requiredMP;
    totalTime = 0.0f;
    for (auto it : _src->childList)
    {
        Skill* pSkill = new Skill(it);
        pSkill->initialize();
        childList.push_back(pSkill);
    }
}

Skill::Skill(const Rect2f& _rect)
{
	shape = _rect;
}

Skill::~Skill()
{

}

Vector2f Skill::calcSkillPos()
{
    float width = 0.0f;
    float height = 0.0f;
    if (!textureKeyList.empty())
    {
        DXTexture* texture = DXTextureManager::getInstance()->getTexture(textureKeyList[state]);
        width = texture->getWidth();
        height = texture->getHeight();
    }
   
    float x = 0.0f;
    float y = 0.0f;
    if (user->currentDirection == Player::Direction::Left)
    {
        x = user->shape.cx() - width + offset.x;
        y = user->shape.RB.y - height + offset.y; //user->shape.cy() - height; //user->shape.RB.y - height;
    }
    else
    {
        x = user->shape.cx() - offset.x;
        y = user->shape.RB.y - height + offset.y; //user->shape.cy() - height; //user->shape.RB.y - height;
    }

    float hitbox_x = x + offset_hitbox.x;
    float hitbox_y = y + offset_hitbox.y;
    float hitbox_width = width - (offset_hitbox.x * 2.0f);
    float hitbox_height = height - (offset_hitbox.y * 2.0f);

    this->shape = Rect2f(x, y, width, height);
    this->hitbox = Rect2f(hitbox_x, hitbox_y, hitbox_width, hitbox_height);

    std::vector<Vertex>* UserVertexList = user->pShader->getVertexList();
    std::vector<Vertex>* skillVertexList = pShader->getVertexList();
    skillVertexList->at(0).texture = UserVertexList->at(0).texture;
    skillVertexList->at(1).texture = UserVertexList->at(1).texture;
    skillVertexList->at(2).texture = UserVertexList->at(2).texture;
    skillVertexList->at(3).texture = UserVertexList->at(3).texture;

    return Vector2f(x, y);
}

bool Skill::isCoolDown()
{
    if (totalTime >= coolTime)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Skill::Load(std::wstring _path)
{
    std::filesystem::path path(_path);
    for (auto& file : std::filesystem::directory_iterator(path))
    {
        std::wstring filepath = file.path();
        std::wstring filename = file.path().filename();
        std::wstring fileExtension = file.path().extension();

        if (fileExtension == L"")
        {
            std::wstring dir = filepath + L"/";
            Skill* childSkill = new Skill;
            childSkill->user = user;
            if (childSkill->Load(dir))
            {
                childSkill->initialize();
                childList.push_back(childSkill);
            }
            else
            {
                delete childSkill;
                childSkill = nullptr;
                return false;
            }
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

bool Skill::LoadInfo(std::wstring _path)
{
    std::fstream file(_path);
    if (!file.is_open())
    {
        return false;
    }
    else
    {
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
            else if (dataName == "coolTime")
            {
                std::string lineData;
                std::getline(file, lineData, '\n');
                coolTime = std::stof(lineData);
            }
            else if (dataName == "damageCount")
            {
                std::string lineData;
                std::getline(file, lineData, '\n');
                int damageCount = std::stoi(lineData);
                for (int cnt = 0; cnt < damageCount; cnt++)
                {
                    std::getline(file, lineData, '\n');
                    damageList.push_back(std::stof(lineData));
                }
            }
            else if (dataName == "offset_x")
            {
                std::string lineData;
                std::getline(file, lineData, '\n');
                offset.x = std::stof(lineData);
            }
            else if (dataName == "offset_y")
            {
                std::string lineData;
                std::getline(file, lineData, '\n');
                offset.y = std::stof(lineData);
            }
            else if (dataName == "offset_hitbox_x")
            {
                std::string lineData;
                std::getline(file, lineData, '\n');
                offset_hitbox.x = std::stof(lineData);
            }
            else if (dataName == "offset_hitbox_y")
            {
                std::string lineData;
                std::getline(file, lineData, '\n');
                offset_hitbox.y = std::stof(lineData);
            }
            else if (dataName == "mp")
            {
                std::string lineData;
                std::getline(file, lineData, '\n');
                requiredMP = std::stof(lineData);
            }
            else if (dataName == "hitstate")
            {
                std::string lineData;
                std::getline(file, lineData, '\n');
                hitState = std::stoi(lineData);
            }
        }
        file.close();
        return true;
    }

    return false;
}

bool Skill::initialize()
{
    Effect::initialize();
   
    //coolTime = 0.0f;
    isCancel = false;
    
    this->mapWidth = user->mapWidth;
    this->mapHeight = user->mapHeight;

    Vector2f skillPos = calcSkillPos();
    //moveTo(skillPos);

    this->setCamera(user->renderCamera);
    
    childState = 0;
    for (auto it : childList)
    {
        it->initialize();
        it->skillName = skillName;
    }
   
    beforeTime = Timer::getInstance()->getPlayTime();
   
    return true; // this->createShader(ShaderType::Texture);
}

bool Skill::frame()
{
    float currentTime = Timer::getInstance()->getPlayTime();
    float secondPerFrame = currentTime - beforeTime;
    this->timeCounter += secondPerFrame;
    this->totalTime += secondPerFrame;
    beforeTime = currentTime;

    if (this->isEnd)
    {
        return true;
    }
        
    if (!childList.empty())
    {
        if (isCancel)
        {
            isEnd = true;
            return true;
        }
        else
        {
            Skill* currentSkill = childList[childState];
            if (!currentSkill->isEnd)
            {
                currentSkill->frame();
                return true;
            }
            else
            {
                if (childState < childList.size() - 1)
                {
                    childState++;
                }
                else
                {
                    childState = 0;
                    isEnd = true;
                }
            }
        }

    }
    else
    {
        if (timeCounter >= frameTime)
        {
            timeCounter = 0.0f;

            std::wstring strTime = L"Skill[" + std::to_wstring(state) + L"] Time: " + std::to_wstring(frameTime) + L"\n";
            OutputDebugString(strTime.c_str());
            calcSkillPos();
            //moveTo(calcSkillPos());

            if (state == hitState)
            {
                std::vector<object2D<float>*> collisionList;
                std::vector<Rect2f> collisionRectList;
                user->currentMap->Collision(this, &collisionList, &collisionRectList);

                std::vector<float> hitPoint;
                for (auto it : damageList)
                {
                    float damage = user->info.getAttackPoint() * (it / 100.0f);
                    hitPoint.push_back(damage);
                }

                //for (auto it : collisionList)
                //{
                //    NPC* pMonster = dynamic_cast<NPC*>(it);
                //    for (auto it2 : hitPoint)
                //    {
                //        pMonster->hit(user, it2, );
                //    }                     
                //}
                //
                //for (auto it : collisionRectList)
                //{
                //    EffectManager::getInstance()->addEffectToJobList(it.center(), skillName);
                //    DrawBorder(it, BORDER_COLOR_BLUE);
                //}

                for (size_t idx = 0; idx < collisionList.size(); idx++)
                {
                    NPC* pMonster = dynamic_cast<NPC*>(collisionList[idx]);
                    NPC::Direction hitDirection;
                    if (pMonster->shape.cx() < collisionRectList[idx].cx())
                    {
                        hitDirection = NPC::Direction::Right;
                    }
                    else if(pMonster->shape.cx() > collisionRectList[idx].cx())
                    {
                        hitDirection = NPC::Direction::Left;
                    }
                    else
                    {
                        if (user->currentDirection == Player::Direction::Right)
                        {
                            hitDirection = NPC::Direction::Left;
                        }
                        else
                        {
                            hitDirection = NPC::Direction::Right;
                        }
                    }

                    Vector2f damagePos = collisionRectList[idx].center();
                    for (auto iterDamage : hitPoint)
                    {
                        pMonster->hit(user, iterDamage, hitDirection);
                        EffectManager::getInstance()->addDamageEffectToJobList(damagePos, L"Attack", iterDamage);
                        damagePos.y -= 30;
                    }

                    if (pMonster->isDie())
                    {
                        user->info.currentExp += pMonster->info.exp;
                    }

                    EffectManager::getInstance()->addEffectToJobList(collisionRectList[idx].center(), skillName);
                    DrawBorder(collisionRectList[idx], BORDER_COLOR_BLUE);
                }

            }

            if (state < textureKeyList.size() - 1)
            {
                state++;
            }
            else
            {
                state = 0;
                //user->currentMap->updateDynamicObject();

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

	return true;
}

bool Skill::render()
{
    if (!childList.empty())
    {
        Skill* currentSkill = childList[childState];
        currentSkill->render();
    }
    else
    {
        object2D<float>::render();
        DrawBorder(hitbox, BORDER_COLOR_GREEN);
    }
	
	return true;
}

bool Skill::release()
{
	return true;
}