#pragma once
#include "Object.hpp"
#include "DXShaderBorderManager.hpp"
#include "Map.hpp"
#include "Camera.hpp"
#include <fstream>
#include "PlayerInfo.hpp"

class UserState;

class Player : public object2D<float>
{
protected:
	UserState* currentState;

public:
	//object2D<float>* pObj;
	
	PlayerInfo info;

	enum class Direction
	{
		Left,
		Right
	};

	bool invincible = false;
	bool doubleJump = false;
	bool isDie = false;
	float beforeTime = 0.0f;
	float collisionTimeCounter = 0.0f;
	float invincibleTimeCounter = 0.0f;
	float HPregenerateTime = 0.0f;
	float frameTime = 0.0f;

	Direction currentDirection = Direction::Left;

	Map* currentMap = nullptr;

public:
	Player();
	Player(const Rect2f& _rect);
	virtual ~Player();

public:
	virtual bool initialize();
	virtual bool frame(float _dt);
	virtual bool render();
	virtual bool release();

public:
	void setCamera(Camera* _camera);

public:
	Rect2f getRect();
	Vector2f getCenter();

public:
	void hit(float _damage);

public:
	template <typename T>
	void changeCurrentState();
};

template <typename T>
void Player::changeCurrentState()
{
	delete currentState;
	currentState = nullptr;
	currentState = new T(this);
}