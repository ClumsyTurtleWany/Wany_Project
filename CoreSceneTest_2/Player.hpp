#pragma once
#include "Object.hpp"
#include "DXShaderBorderManager.hpp"
#include "SpaceDivision.hpp"
#include "Camera.hpp"

class UserState;

class Player : public object2D<float>
{
protected:
	UserState* currentState;

public:
	//object2D<float>* pObj;
	
	enum class Direction
	{
		Left,
		Right
	};

	Direction currentDirection = Direction::Right;

	SpaceDivision* currentMap;

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