#pragma once
#include "Define.hpp"
#include "DXShaderManager.hpp"

static int objectCnt = 0;

enum class OBJECT_TYPE
{
	STATIC_OBJECT,
	DYNAMIC_OBJECT
};

class objectBase
{
private:
	int object_id = 0;

public:
	// Direct X
	DXShader* pShader = nullptr;

public:
	std::vector<Rect_<float>> SpriteList;
	int SpriteNum = 0;

public:
	// Common
	std::string name;
	float mass = 0.0f;
	OBJECT_TYPE type = OBJECT_TYPE::STATIC_OBJECT;

public:
	objectBase() {	object_id = objectCnt++; };
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
	void createShader(ShaderType _type = ShaderType::Mask);
	void setTexture(DXTexture* _texture);
	void setTextureMask(DXTexture* _mask);
	void setColor(Vector4f _color);
	void setSpriteList(const std::vector<Rect_<float>>& _list);
};



template <typename T>
class object2D : public objectBase
{
public:
	Rect_<T> shape;
	Vector2D_<T> force;
	Vector2D_<T> accel;
	Vector2D_<T> velocity;

//public:
//	std::vector<Rect_<float>> SpriteList;
//	int SpriteNum = 0;

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
		RECT clientRect = g_pWindow->getClientRect();
		shape = Rect_<T>(rand() % clientRect.right, rand() % clientRect.bottom, 50 + (rand() % 20), 50 + (rand() % 20));
		this->mass = 100 + rand() % 100;
		//int testForce = 50 + rand() % 50;
		//this->force = Vector2D_<T>(100 + rand() % 200, 100 + rand() % 200);
		//this->force = Vector2D_<T>(testForce, testForce);

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

	void moveTo(T _x, T _y)
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
		pShader->render();

		return true;
	}

public:
	void updateShader()
	{
		RECT clientRect = g_pWindow->getClientRect();
		float mapWidth = clientRect.right - clientRect.left; // clientRectWidth;
		float mapHeight = clientRect.bottom - clientRect.top; // clientRectHeight;
		float mapWidth_Half = mapWidth * 0.5;
		float mapHeight_Half = mapHeight * 0.5;

		Rect_<float> rectNDC;
		rectNDC.LT.x = (shape.LT.x - mapWidth_Half) / mapWidth_Half;
		rectNDC.LT.y = -(shape.LT.y - mapHeight_Half) / mapHeight_Half;
		rectNDC.RB.x = (shape.RB.x - mapWidth_Half) / mapWidth_Half;
		rectNDC.RB.y = -(shape.RB.y - mapHeight_Half) / mapHeight_Half;

		//std::vector<Vertex> list;
		//list.assign(4, Vertex());
		//list[0].pos = { rectNDC.LT.x, rectNDC.LT.y, 0.0f };
		//list[1].pos = { rectNDC.RB.x, rectNDC.LT.y, 0.0f };
		//list[2].pos = { rectNDC.LT.x, rectNDC.RB.y, 0.0f };
		//list[3].pos = { rectNDC.RB.x, rectNDC.RB.y, 0.0f };

		std::vector<Vertex>*list = pShader->getVertexList();
		list->at(0).pos = { rectNDC.LT.x, rectNDC.LT.y, 0.0f };
		list->at(1).pos = { rectNDC.RB.x, rectNDC.LT.y, 0.0f };
		list->at(2).pos = { rectNDC.LT.x, rectNDC.RB.y, 0.0f };
		list->at(3).pos = { rectNDC.RB.x, rectNDC.RB.y, 0.0f };

		//if (!SpriteList.empty())
		//{
		//	// Set Sprite Region
		//	float textureWidth = pShader->getTextureWidth();
		//	float textureHeight = pShader->getTextureHeight();

		//	Rect_<float> rect = SpriteList[SpriteNum];
		//	list[0].texture = { rect.left() / textureWidth, rect.top() / textureHeight }; // p1-LT
		//	list[1].texture = { rect.right() / textureWidth, rect.top() / textureHeight }; // p2-RT
		//	list[2].texture = { rect.left() / textureWidth, rect.bottom() / textureHeight }; // p3-LB
		//	list[3].texture = { rect.right() / textureWidth, rect.bottom() / textureHeight }; // p4-RB
		//}
		//else
		//{
		//	list[0].texture = { 0.0f, 0.0f }; // p1-LT
		//	list[1].texture = { 1.0f, 0.0f }; // p2-RT
		//	list[2].texture = { 0.0f, 1.0f }; // p3-LB
		//	list[3].texture = { 1.0f, 1.0f }; // p4-RB
		//}

		if (!SpriteList.empty())
		{
			// Set Sprite Region
			float textureWidth = pShader->getTextureWidth();
			float textureHeight = pShader->getTextureHeight();

			Rect_<float> rect = SpriteList[SpriteNum];
			list->at(0).texture = { rect.left() / textureWidth, rect.top() / textureHeight }; // p1-LT
			list->at(1).texture = { rect.right() / textureWidth, rect.top() / textureHeight }; // p2-RT
			list->at(2).texture = { rect.left() / textureWidth, rect.bottom() / textureHeight }; // p3-LB
			list->at(3).texture = { rect.right() / textureWidth, rect.bottom() / textureHeight }; // p4-RB
		}
		else
		{
			list->at(0).texture = { 0.0f, 0.0f }; // p1-LT
			list->at(1).texture = { 1.0f, 0.0f }; // p2-RT
			list->at(2).texture = { 0.0f, 1.0f }; // p3-LB
			list->at(3).texture = { 1.0f, 1.0f }; // p4-RB

			// flip
			//list->at(0).texture = { 1.0f, 0.0f }; // p1-RT
			//list->at(1).texture = { 0.0f, 0.0f }; // p2-LT
			//list->at(2).texture = { 1.0f, 1.0f }; // p3-RB
			//list->at(3).texture = { 0.0f, 1.0f }; // p4-LB
		}

		//pShader->setVertexList(list);
	}

protected:
	DXShader* getShader()
	{
		return pShader;
	}

protected:
	void setSpriteNum(int _num)
	{
		SpriteNum = _num;
	}

	int getSpriteNum()
	{
		return SpriteNum;
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

	void moveTo(T _x, T _y, T _z)
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
		pShader->render();
		return true;
	}

protected:
	DXShader* getShader()
	{
		return pShader;
	}
};