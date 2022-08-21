#pragma once
#include "Rect.hpp"
#include "Cube.hpp"
#include "Vector.hpp"
#include "Circle.hpp"
#include <string>

enum class OBJECT_TYPE
{
	STATIC_OBJECT,
	DYNAMIC_OBJECT
};

template <class Shape, class VectorDimension>
class objectBase
{
public:
	// Common
	std::string name;
	float mass = 0.0f;
	OBJECT_TYPE type = OBJECT_TYPE::STATIC_OBJECT;

	Shape shape;
	VectorDimension force;
	VectorDimension accel;
	VectorDimension velocity;

public:
	objectBase() {};
	~objectBase() {};

public:
	virtual void Random() = 0;
	virtual void frame(float _dt) = 0;
	virtual void moveTo(VectorDimension _pos) = 0;
	virtual void render() = 0;
};

template <typename T>
class object2D : public objectBase<Rect_<T>, Vector2D_<T>>
{
public:
	object2D() {};
	object2D(Rect_<T> _rect, OBJECT_TYPE _type = OBJECT_TYPE::STATIC_OBJECT)
	{
		this->shape = _rect;
		this->type = _type;
		this->mass = 0.0f;
	};
	~object2D() {};

public:
	void Random()
	{
		this->shape = Rect_<T>(20 + rand() % 80, 20 + rand() % 80, 2 + (rand() % 20), 2 + (rand() % 20));
		this->mass = rand() % 200;
		this->force = Vector2D_<T>(rand() % 200, rand() % 200);
	}

	void moveTo(Vector2D_<T> _pos) override
	{
		if (this->type == OBJECT_TYPE::DYNAMIC_OBJECT)
		{
			Vector2D_<T> offset = _pos - this->shape.LT;
			this->shape.offset(offset);
		}
	}

	void moveTo(Point_<T> _pos)
	{
		if (this->type == OBJECT_TYPE::DYNAMIC_OBJECT)
		{
			Point_<T> offset = _pos - this->shape.LT;
			this->shape.offset(offset);
		}
	}

	void moveTo(int _x, int _y)
	{
		if (this->type == OBJECT_TYPE::DYNAMIC_OBJECT)
		{
			moveTo(Point_<T>(_x, _y));
		}
	}

	Circle_<T> getCircle()
	{
		return Circle_<T>(this->shape.center(), this->shape.length() / 2.0f);
	}

public:
	virtual void frame(float _dt);
	virtual void render()
	{
		std::cout << "[ " << this->name << " ] - ";
		std::cout << "L: " << this->shape.left() << ", ";
		std::cout << "T: " << this->shape.top() << ", ";
		std::cout << "R: " << this->shape.right() << ", ";
		std::cout << "B: " << this->shape.bottom() << std::endl;
	}
};

template <typename T>
class object3D : public objectBase<Box_<T>, Vector3D_<T>>
{
public:
	object3D() {};
	object3D(Box_<T> _box, OBJECT_TYPE _type = OBJECT_TYPE::STATIC_OBJECT)
	{
		this->shape = _box;
		this->type = _type;
		this->mass = 0.0f;
	}
	~object3D() {};

public:
	void Random()
	{
		this->shape = Box_<T>(Point3D_<T>(20 + rand() % 80, 20 + rand() % 80, 20 + rand() % 80), 2 + (rand() % 20), 2 + (rand() % 20), 2 + (rand() % 20));
		this->mass = rand() % 200;
		this->force = Vector3D_<T>(rand() % 200, rand() % 200, rand() % 200);
	}

	void moveTo(Vector3D_<T> _pos) override
	{
		if (this->type == OBJECT_TYPE::DYNAMIC_OBJECT)
		{
			Vector3D_<T> offset = _pos - this->shape.pos;
			this->shape.offset(offset);
		}
	}

	void moveTo(Point3D_<T> _pos)
	{
		if (this->type == OBJECT_TYPE::DYNAMIC_OBJECT)
		{
			Point3D_<T> offset = _pos - this->shape.pos;
			this->shape.offset(offset);
		}
	}

	void moveTo(int _x, int _y, int _z)
	{
		if (this->type == OBJECT_TYPE::DYNAMIC_OBJECT)
		{
			moveTo(Point3D_<T>(_x, _y, _z));
		}
	}

	Sphere_<T> getSphere()
	{
		return Sphere_<T>(this->shape.center(), this->shape.length() / 2.0f);
	}

public:
	virtual void frame(float _dt) {};
	virtual void render()
	{
		std::cout << "[ " << this->name << " ] - ";
		std::cout << "Pos[x]: " << this->shape.pos.x << ", ";
		std::cout << "Pos[y]: " << this->shape.pos.y << ", ";
		std::cout << "Pos[z]: " << this->shape.pos.z << ", ";
		std::cout << "width: " << this->shape.width << ", ";
		std::cout << "height: " << this->shape.height << ", ";
		std::cout << "depth: " << this->shape.depth << std::endl;
	}
};

using Object = object3D<float>;