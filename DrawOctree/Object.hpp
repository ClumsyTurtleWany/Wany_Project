#pragma once
#include "Define.hpp"
#include "DXShader.hpp"

enum class OBJECT_TYPE
{
	STATIC_OBJECT,
	DYNAMIC_OBJECT
};

class objectBase
{
public:
	// Direct X
	DXShader shader;

public:
	// Common
	std::string name;
	float mass = 0.0f;
	OBJECT_TYPE type = OBJECT_TYPE::STATIC_OBJECT;

public:
	objectBase() {};
	~objectBase() {};

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool frame(float _dt) = 0;
	virtual bool render();
	virtual bool release();
	virtual bool Random() = 0;

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
	
};

bool objectBase::initialize()
{
	return shader.initialize();
}

bool objectBase::frame()
{
	return true;
}

bool objectBase::render()
{
	return shader.render();
}

bool objectBase::release()
{
	return shader.release();
}

void objectBase::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	shader.setDevice(_device, _context);
}

template <typename T>
class object2D : public objectBase
{
public:
	Rect_<T> shape;
	Vector2D_<T> force;
	Vector2D_<T> accel;
	Vector2D_<T> velocity;

public:
	object2D() {};
	object2D(Rect_<T> _rect, OBJECT_TYPE _type = OBJECT_TYPE::STATIC_OBJECT)
	{
		shape = _rect;
		this->type = _type;
		this->mass = 0.0f;
	};
	~object2D() {};

public:
	bool Random()
	{
		shape = Rect_<T>(30 + rand() % 70, 30 + rand() % 70, 5 + (rand() % 20), 5 + (rand() % 20));
		this->mass = 50 + rand() % 150;
		this->force = Vector2D_<T>(100 + rand() % 200, 100 + rand() % 200);

		return true;
	}

	void moveTo(Vector2D_<T> _pos)
	{
		Vector2D_<T> offset = _pos - this->shape.LT;
		this->shape.offset(offset);
	}

	void moveTo(Point_<T> _pos)
	{
		Point_<T> offset = _pos - this->shape.LT;
		this->shape.offset(offset);
	}

	void moveTo(int _x, int _y)
	{
		moveTo(Point_<T>(_x, _y));
	}

	Circle_<T> getCircle()
	{
		return Circle_<T>(this->shape.center(), this->shape.length() / 2.0f);
	}

public:
	virtual bool frame(float _dt) { return true; };
	bool render() override
	{
		updateShader();
		shader.render();
		std::cout << "[ " << this->name << " ] - ";
		std::cout << "L: " << this->shape.left() << ", ";
		std::cout << "T: " << this->shape.top() << ", ";
		std::cout << "R: " << this->shape.right() << ", ";
		std::cout << "B: " << this->shape.bottom() << std::endl;

		return true;
	}

public:
	void updateShader()
	{
		float mapWidth = 128.0f;
		float mapHeight = 128.0f;
		float mapWidth_Half = mapWidth * 0.5;
		float mapHeight_Half = mapHeight * 0.5;

		Rect_<float> rectNDC;
		rectNDC.LT.x = (shape.LT.x - mapWidth_Half) / mapWidth_Half;
		rectNDC.LT.y = -(shape.LT.y - mapHeight_Half) / mapWidth_Half;
		rectNDC.RB.x = (shape.RB.x - mapWidth_Half) / mapWidth_Half;
		rectNDC.RB.y = -(shape.RB.y - mapHeight_Half) / mapWidth_Half;

		std::vector<Vertex> list;
		list.assign(6, Vertex());
		list[0].pos = { rectNDC.LT.x, rectNDC.LT.y, 0.0f };
		list[1].pos = { rectNDC.RB.x, rectNDC.LT.y, 0.0f };
		list[2].pos = { rectNDC.LT.x, rectNDC.RB.y, 0.0f };
		list[3].pos = { rectNDC.LT.x, rectNDC.RB.y, 0.0f };
		list[4].pos = { rectNDC.RB.x, rectNDC.LT.y, 0.0f };
		list[5].pos = { rectNDC.RB.x, rectNDC.RB.y, 0.0f };

		list[0].color = { 0.0f, 1.0f, 0.0f, 0.0f};
		list[1].color = { 0.0f, 1.0f, 0.0f, 0.0f};
		list[2].color = { 0.0f, 1.0f, 0.0f, 0.0f};
		list[3].color = { 0.0f, 1.0f, 0.0f, 0.0f};
		list[4].color = { 0.0f, 1.0f, 0.0f, 0.0f};
		list[5].color = { 0.0f, 1.0f, 0.0f, 0.0f};
		shader.setVertexList(list);
	}

protected:
	DXShader* getShader()
	{
		return &shader;
	}
};

template <typename T>
class object3D : public objectBase
{
public:
	Box_<T> shape;
	Vector3D_<T> force;
	Vector3D_<T> accel;
	Vector3D_<T> velocity;

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
	bool Random()
	{
		this->shape = Box_<T>(Point3D_<T>(30 + rand() % 70, 30 + rand() % 70, 30 + rand() % 70), 20 + (rand() % 10), 20 + (rand() % 10), 20 + (rand() % 10));
		this->mass = 50 + rand() % 150;
		this->force = Vector3D_<T>(100 + rand() % 200, 100 + rand() % 200, 100 + rand() % 200);

		return true;
	}

	void moveTo(Vector3D_<T> _pos)
	{
		Vector3D_<T> offset = _pos - this->shape.pos;
		this->shape.offset(offset);
	}

	void moveTo(Point3D_<T> _pos)
	{
		Point3D_<T> offset = _pos - this->shape.pos;
		this->shape.offset(offset);
	}

	void moveTo(int _x, int _y, int _z)
	{
		moveTo(Point3D_<T>(_x, _y, _z));
	}

	Sphere_<T> getSphere()
	{
		return Sphere_<T>(this->shape.center(), this->shape.length() / 2.0f);
	}

public:
	virtual bool frame(float _dt) { return true; };
	bool render() override
	{
		shader.render();
		std::cout << "[ " << this->name << " ] - ";
		std::cout << "Pos[x]: " << this->shape.pos.x << ", ";
		std::cout << "Pos[y]: " << this->shape.pos.y << ", ";
		std::cout << "Pos[z]: " << this->shape.pos.z << ", ";
		std::cout << "width: " << this->shape.width << ", ";
		std::cout << "height: " << this->shape.height << ", ";
		std::cout << "depth: " << this->shape.depth << std::endl;

		return true;
	}

protected:
	DXShader* getShader()
	{
		return &shader;
	}
};