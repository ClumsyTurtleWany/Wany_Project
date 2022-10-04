#include "Player.hpp"
#include "UserState_Idle.hpp"
#include "EffectManager.hpp"
#include "NPC.hpp"

Player::Player() : currentState(new UserState_Idle(this))
{
	//pObj = new object2D<float>;
	//pObj->createShader(ShaderType::Texture);
	mass = 1.0f;
}

Player::Player(const Rect2f& _rect) : currentState(new UserState_Idle(this))
{
	//pObj = new object2D<float>(_rect);
	//pObj->createShader(ShaderType::Texture);
	mass = 1.0f;
	shape = _rect;
}

Player::~Player()
{
	release();
}

bool Player::initialize()
{
	beforeTime = Timer::getInstance()->getPlayTime();
	return true;
}

bool Player::frame(float _dt)
{
	float currentTime = Timer::getInstance()->getPlayTime();
	float secondPerFrame = currentTime - beforeTime;
	collisionTimeCounter += secondPerFrame;
	invincibleTimeCounter += secondPerFrame;
	HPregenerateTime += secondPerFrame;
	frameTime += secondPerFrame;

	// default
	object2D<float>::frame(_dt);

	// FSM
	if (!currentState->frame())
	{
		return false;
	}

	// Check Boundary
	Vector2f distance = force * _dt;
	shape.offset(distance);

	if (shape.LT.x < 0)
	{
		Rect2f rectTemp = shape;
		float width = rectTemp.width();
		shape.LT.x = 0;
		shape.RB.x = shape.LT.x + width - 1;
	}

	if (shape.LT.y < 0)
	{
		Rect2f rectTemp = shape;
		shape.LT.y = 0;
		shape.RB.y = shape.LT.y + rectTemp.height() - 1;
	}

	if (shape.RB.x > mapWidth)
	{
		Rect2f rectTemp = shape;
		shape.RB.x = mapWidth;
		shape.LT.x = shape.RB.x - rectTemp.width() + 1;
	}

	if (shape.RB.y > mapHeight)
	{
		Rect2f rectTemp = shape;
		shape.RB.y = mapHeight;
		shape.LT.y = shape.RB.y - rectTemp.height() + 1;
	}

	hitbox = shape;

	// Collision
	if (collisionTimeCounter >= 0.5f)
	{
		if (!invincible)
		{
			std::vector<object2D<float>*> collisionObjList;
			if (currentMap->Collision(this, &collisionObjList))
			{
				NPC* pNpc = dynamic_cast<NPC*>(collisionObjList[0]);
				info.currentHP -= pNpc->info.minDamage;
				EffectManager::getInstance()->addDamageEffectToJobList(hitbox.center(), L"Hit", pNpc->info.minDamage);
				invincible = true;
				collisionTimeCounter = 0.0f;
				invincibleTimeCounter = 0.0f;
			}
		}
	}

	if(invincible)
	{
		if (invincibleTimeCounter >= 2.0f)
		{
			alphaVal = 1.0f;
			invincible = false;
			invincibleTimeCounter = 0.0f;
		}
		else
		{
			if (frameTime >= 0.5f)
			{
				if (alphaVal == 0.5f)
				{
					alphaVal = 1.0f;
				}
				else
				{
					alphaVal = 0.5f;
				}
				frameTime = 0.0f;
			}
		}
	}

	if (HPregenerateTime >= 5.0f)
	{
		HPregenerateTime = 0.0f;
		info.currentHP = info.currentHP + 5 > info.maxHP ? info.maxHP : info.currentHP + 5;
		info.currentMP = info.currentMP + 5 > info.maxMP ? info.maxMP : info.currentMP + 5;
	}
	
	// Level Up
	while (info.requiredExp <= info.currentExp)
	{
		info.currentExp -= info.requiredExp;
		info.level++;
		info.maxHP *= 1.5;
		info.currentHP = info.maxHP;
		info.maxMP *= 1.5;
		info.currentMP = info.maxMP;
		info.requiredExp *= 1.5;
		info.maxDamage++;

		EffectManager::getInstance()->addEffectToJobList(Vector2f(shape.cx(), shape.cy() - 200), L"LevelUp");
	}

	beforeTime = currentTime;

	return true;
}

bool Player::render()
{
	object2D<float>::render();
	/*if (!pObj->render())
	{
		return false;
	}*/

	DrawBorder(hitbox, BORDER_COLOR_RED);

	if (!currentState->render())
	{
		return false;
	}

	//DrawBorder(hitbox, BORDER_COLOR_RED);

	return true;
}

bool Player::release()
{
	//pObj->release();
	//delete pObj;
	//pObj = nullptr;
	return currentState->release();
}

void Player::setCamera(Camera* _camera)
{
	renderCamera = _camera;
}

Rect2f Player::getRect()
{
	return shape;
}

Vector2f Player::getCenter()
{
	return shape.center();
}
