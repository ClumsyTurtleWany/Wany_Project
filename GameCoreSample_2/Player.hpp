#pragma once
#include "Object.hpp"

template <typename T>
class Player2D : public object2D<T> //: public Player<object2D<T>>
{
public:
	Player2D() 
	{
		this->type = OBJECT_TYPE::DYNAMIC_OBJECT;
		this->setSpriteNum(3);
		this->shape = Rect_<float>(500, 500, 100, 100);
		this->mass = 100;
	};
	Player2D(std::string _name, Rect_<T> _rect, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		this->name = _name;
		this->shape = _rect;
		this->type = _type;
	}
	~Player2D() {};

public:
	bool frame(float _dt) override
	{
		int spriteNum = this->getSpriteNum();
		KeyState keyState_W = Input::getInstance()->getKey('W');
		if((keyState_W == KeyState::Down) || (keyState_W == KeyState::Hold))
		{
			this->force.y -= 100 * _dt;
			if (spriteNum == 3)
			{
				this->setSpriteNum(++spriteNum);
			}
		}
		
		KeyState keyState_S = Input::getInstance()->getKey('S');
		if((keyState_S == KeyState::Down) || (keyState_S == KeyState::Hold))
		{
			this->force.y += 100 * _dt;
		}

		if ((keyState_W == KeyState::Free) && (keyState_S == KeyState::Free))
		{
			this->force.y = 0;
			this->velocity.y = 0;
		}

		KeyState keyState_A = Input::getInstance()->getKey('A');
		if ((keyState_A == KeyState::Down) || (keyState_A == KeyState::Hold))
		{
			this->force.x -= 100 * _dt;

			if (spriteNum != 0)
			{
				this->setSpriteNum(--spriteNum);
			}
		}

		KeyState keyState_D = Input::getInstance()->getKey('D');
		if ((keyState_D == KeyState::Down) || (keyState_D == KeyState::Hold))
		{
			this->force.x += 100 * _dt;

			if (spriteNum != 7)
			{
				this->setSpriteNum(++spriteNum);
			}
		}

		if ((keyState_A == KeyState::Free) && (keyState_D == KeyState::Free))
		{
			this->force.x = 0;
			this->velocity.x = 0;

			if (spriteNum != 3)
			{
				if (spriteNum < 3)
				{
					this->setSpriteNum(++spriteNum);
				}
				else
				{
					this->setSpriteNum(--spriteNum);
				}
			}
		}

		OutputDebugStringA((char*)&spriteNum);
		

		// Calculate Accel and Velocity.
		this->accel = this->force / this->mass;
		this->velocity += this->accel * _dt;
		//this->velocity += this->accel * _dt * 0.0001;
		float resistCoef = -0.1f;
		Vector2D_<T> resistForce = this->force * resistCoef * _dt;
		this->force += resistForce;

		this->shape.offset(this->velocity.x, this->velocity.y);

		return true;
	}
};

template <typename T>
class Player3D : public object3D<T> //: public Player<object3D<T>>
{
public:
	Player3D()
	{
		this->type = OBJECT_TYPE::DYNAMIC_OBJECT;
	};

	Player3D(std::string _name, Box_<T> _box, OBJECT_TYPE _type = OBJECT_TYPE::DYNAMIC_OBJECT)
	{
		this->name = _name;
		this->shape = _box;
		this->type = _type;
	}
	~Player3D() {};

public:
	bool frame(float _dt) override
	{
		this->accel = this->force / this->mass;
		this->velocity += this->accel * _dt;
		float resistCoef = -0.1f;
		Vector3D_<T> resistForce = this->force * resistCoef * _dt;
		this->force += resistForce;

		this->shape.offset(this->velocity.x, this->velocity.y, this->velocity.z);

		return true;
	}
};