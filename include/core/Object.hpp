#pragma once
#include "Define.hpp"
#include "DXShaderManager.hpp"
#include "Camera.hpp"

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
	bool createShader(ShaderType _type = ShaderType::Mask);
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
	Rect_<T> hitbox;
	Vector2D_<T> force;
	Vector2D_<T> accel;
	Vector2D_<T> velocity;

	Camera* renderCamera;

	float angle = 0.0f;
	float mapWidth = 0.0f;
	float mapHeight = 0.0f;

//public:
//	std::vector<Rect_<float>> SpriteList;
//	int SpriteNum = 0;

public:
	object2D() {};
	object2D(Rect_<T> _rect, OBJECT_TYPE _type = OBJECT_TYPE::STATIC_OBJECT)
	{
		shape = _rect;
		hitbox = _rect;
		this->type = _type;
		this->mass = 0.0f;
	};
	~object2D() {};

public:
	virtual bool Random()
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

	// 2022-09-16 Test
	Rect_<T> ScreenToNDC()
	{
		RECT clientRect = g_pWindow->getClientRect();
		float clientWidth = static_cast<float>(clientRect.right - clientRect.left); // clientRectWidth;
		float clientHeight = static_cast<float>(clientRect.bottom - clientRect.top); // clientRectHeight;
		float mapWidth_Half = mapWidth * 0.5f;
		float mapHeight_Half = mapHeight * 0.5f;

		Rect_<T> rectNDC;
		rectNDC.LT.x = (shape.LT.x - mapWidth_Half) / mapWidth_Half;
		rectNDC.LT.y = -(shape.LT.y - mapHeight_Half) / mapHeight_Half;
		rectNDC.RB.x = (shape.RB.x - mapWidth_Half) / mapWidth_Half;
		rectNDC.RB.y = -(shape.RB.y - mapHeight_Half) / mapHeight_Half;

		return rectNDC;
	}

	// 2022-09-20 Test
	// Local->World (Screen to Orthogonal Coordinate)
	Rect_<T> ScreenToOrthogonal(const Rect_<T>& _screen)
	{
		// m_vPos
		// m_rtCollision
		float mapWidth_Half = mapWidth * 0.5f;
		float mapHeight_Half = mapHeight * 0.5f;

		Rect_<T> rectOrthogonal;
		rectOrthogonal.LT.x = _screen.LT.x - mapWidth_Half;
		rectOrthogonal.LT.y = mapHeight_Half - _screen.LT.y;
		rectOrthogonal.RB.x = _screen.RB.x - mapWidth_Half;
		rectOrthogonal.RB.y = mapHeight_Half - _screen.RB.y;

		return rectOrthogonal;
	}

	// 2022-09-20 Test
	// View->NDC (View to NDC)
	Rect_<T> OrthogonalToNDC(const Rect_<T>& _Orthogonal)
	{
		RECT rectTemp = g_pWindow->getClientRect();
		float width = rectTemp.right - rectTemp.left;
		float height = rectTemp.bottom - rectTemp.top;
		float width_half = width * 0.5f;
		float height_half = height * 0.5f;

		//Rect_<T> rectView;
		//rectView.LT.x = (_Orthogonal.LT.x - rectCamera.LT.x);
		//rectView.LT.y = (_Orthogonal.LT.y - rectCamera.LT.y);
		//rectView.RB.x = (_Orthogonal.RB.x - rectCamera.LT.x);
		//rectView.RB.y = (_Orthogonal.RB.y - rectCamera.LT.y);

		Rect_<T> rectNDC;
		rectNDC.LT.x = (_Orthogonal.LT.x - width_half) / width_half;
		rectNDC.LT.y = (_Orthogonal.LT.y + height_half) / height_half;
		rectNDC.RB.x = (_Orthogonal.RB.x - width_half) / width_half;
		rectNDC.RB.y = (_Orthogonal.RB.y + height_half) / height_half;

		return rectNDC;
	}

	// 2022-09-23 Test
	// View->NDC (View to NDC)
	Rect_<T> OrthogonalToNDC_Camera(const Rect_<T>& _Orthogonal)
	{
		if (renderCamera == nullptr)
		{
			return Rect_<T>();
		}

		Rect_<T> rectCamera = ScreenToOrthogonal(renderCamera->getRect());
		Rect_<T> rectView;
		rectView.LT.x = (_Orthogonal.LT.x - rectCamera.LT.x);
		rectView.LT.y = (_Orthogonal.LT.y - rectCamera.LT.y);
		rectView.RB.x = (_Orthogonal.RB.x - rectCamera.LT.x);
		rectView.RB.y = (_Orthogonal.RB.y - rectCamera.LT.y);

		float width = rectCamera.RB.x - rectCamera.LT.x;
		float height = rectCamera.LT.y - rectCamera.RB.y;
		float width_half = width * 0.5f;
		float height_half = height * 0.5f;

		Rect_<T> rectNDC;
		rectNDC.LT.x = (rectView.LT.x - width_half) / width_half;
		rectNDC.LT.y = (rectView.LT.y + height_half) / height_half;
		rectNDC.RB.x = (rectView.RB.x - width_half) / width_half;
		rectNDC.RB.y = (rectView.RB.y + height_half) / height_half;

		return rectNDC;
	}

	// 2022-09-20 Test
	// NDC->View Port
	//Rect_<T> NDC2ViewPort(const Rect_<T>& _NDC)
	//{
	//	RECT clientRect = g_pWindow->getClientRect();
	//	float clientWidth = clientRect.right - clientRect.left; // clientRectWidth;
	//	float clientHeight = clientRect.bottom - clientRect.top; // clientRectHeight;
	//	
	//	Rect_<T> rectNDC;
	//	rectNDC.LT.x = (_Orthogonal.LT.x / mapWidth_Half);
	//	rectNDC.LT.y = (_Orthogonal.LT.y / mapHeight_Half);
	//	rectNDC.RB.x = (_Orthogonal.RB.x / mapWidth_Half);
	//	rectNDC.RB.y = (_Orthogonal.RB.y / mapHeight_Half);
	//}


	Rect_<T> calcTextureRect(const Rect_<T>& _Orthogonal, const Rect_<T>& _cameraOrtho)
	{
		Rect_<T> rectTexture;
		// -2000, 1500 && -500, 380 -> 0.375, 0.25  
		// 2000, -1500 && 500, -380 -> 0.625, 
		rectTexture.LT.x = ((_cameraOrtho.LT.x - _Orthogonal.LT.x) / mapWidth);
		rectTexture.LT.y = ((_Orthogonal.LT.y - _cameraOrtho.LT.y) / mapHeight);
		rectTexture.RB.x = 1.0f - ((_cameraOrtho.RB.x - _Orthogonal.RB.x) / mapWidth);
		rectTexture.RB.y = 1.0f - ((_Orthogonal.RB.y - _cameraOrtho.RB.y) / mapHeight);

		return rectTexture;

	}


public:
	virtual bool frame(float _dt) {	return true; };
	virtual bool render() override
	{
		if (renderCamera != nullptr)
		{
			updateShaderCamera();
		}
		else
		{
			updateShader();
		}
		
		pShader->render();

		return true;
	}

public:
	virtual void updateShader()
	{
		//RECT clientRect = g_pWindow->getClientRect();
		//float mapWidth = clientRect.right - clientRect.left; // clientRectWidth;
		//float mapHeight = clientRect.bottom - clientRect.top; // clientRectHeight;
		//float mapWidth_Half = mapWidth * 0.5;
		//float mapHeight_Half = mapHeight * 0.5;

		//Rect_<float> rectNDC;
		//rectNDC.LT.x = (shape.LT.x - mapWidth_Half) / mapWidth_Half;
		//rectNDC.LT.y = -(shape.LT.y - mapHeight_Half) / mapHeight_Half;
		//rectNDC.RB.x = (shape.RB.x - mapWidth_Half) / mapWidth_Half;
		//rectNDC.RB.y = -(shape.RB.y - mapHeight_Half) / mapHeight_Half;

		Rect_<float> rectNDC;
		rectNDC = ScreenToNDC();
		

		//rectNDC = ScreenToCamera();

		// Vectex List
		std::vector<Vertex>*list = pShader->getVertexList();
		list->at(0).pos = { rectNDC.LT.x, rectNDC.LT.y, 0.0f };
		list->at(1).pos = { rectNDC.RB.x, rectNDC.LT.y, 0.0f };
		list->at(2).pos = { rectNDC.LT.x, rectNDC.RB.y, 0.0f };
		list->at(3).pos = { rectNDC.RB.x, rectNDC.RB.y, 0.0f };

		//float width = rectNDC.fWidth();
		//float height = rectNDC.fHeight();
		//list->at(0).pos = { rectNDC.LT.x, rectNDC.LT.y, 0.0f };
		//list->at(1).pos = { rectNDC.LT.x + rectNDC.width(), rectNDC.LT.y, 0.0f };
		//list->at(2).pos = { rectNDC.LT.x, rectNDC.LT.y + rectNDC.height(), 0.0f };
		//list->at(3).pos = { rectNDC.LT.x + rectNDC.width(), rectNDC.LT.y + rectNDC.height(), 0.0f };

		//list->at(0).texture = { 0.0f, 0.0f }; // p1-LT
		//list->at(1).texture = { 1.0f, 0.0f }; // p2-RT
		//list->at(2).texture = { 0.0f, 1.0f }; // p3-LB
		//list->at(3).texture = { 1.0f, 1.0f }; // p4-RB

		if (0)
		{
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
		}
	}

	// 2022-09-22 Test
	virtual void updateShaderCamera()
	{
		//RECT clientRect = g_pWindow->getClientRect();
		//float mapWidth = clientRect.right - clientRect.left; // clientRectWidth;
		//float mapHeight = clientRect.bottom - clientRect.top; // clientRectHeight;
		//float mapWidth_Half = mapWidth * 0.5;
		//float mapHeight_Half = mapHeight * 0.5;

		//Rect_<float> rectNDC;
		//rectNDC.LT.x = (shape.LT.x - mapWidth_Half) / mapWidth_Half;
		//rectNDC.LT.y = -(shape.LT.y - mapHeight_Half) / mapHeight_Half;
		//rectNDC.RB.x = (shape.RB.x - mapWidth_Half) / mapWidth_Half;
		//rectNDC.RB.y = -(shape.RB.y - mapHeight_Half) / mapHeight_Half;

		Rect_<float> rectOrthogonal = ScreenToOrthogonal(shape);
		Rect_<float> rectNDC;
		if (renderCamera != nullptr)
		{
			rectNDC = OrthogonalToNDC_Camera(rectOrthogonal);
		}
		else
		{
			rectNDC = OrthogonalToNDC(rectOrthogonal);
		}
		

		

		//Rect_<float> rectTexture = calcTextureRect(rectOrthogonal, rectCameraOrtho);

		//rectTexture.LT.x = 0.375f;
		//rectTexture.LT.y = 0.375f;
		//rectTexture.RB.x = 0.625f;
		//rectTexture.RB.y = 0.625f;

		// Vectex List
		std::vector<Vertex>* list = pShader->getVertexList();
		list->at(0).pos = { rectNDC.LT.x, rectNDC.LT.y, 0.0f };
		list->at(1).pos = { rectNDC.RB.x, rectNDC.LT.y, 0.0f };
		list->at(2).pos = { rectNDC.LT.x, rectNDC.RB.y, 0.0f };
		list->at(3).pos = { rectNDC.RB.x, rectNDC.RB.y, 0.0f };


		//list->at(0).texture = { 0.0f, 0.0f }; // p1-LT
		//list->at(1).texture = { 1.0f, 0.0f }; // p2-RT
		//list->at(2).texture = { 0.0f, 1.0f }; // p3-LB
		//list->at(3).texture = { 1.0f, 1.0f }; // p4-RB

		//list->at(0).texture = { rectTexture.LT.x, rectTexture.LT.y }; // p1-LT
		//list->at(1).texture = { rectTexture.RB.x, rectTexture.LT.y }; // p2-RT
		//list->at(2).texture = { rectTexture.LT.x, rectTexture.RB.y }; // p3-LB
		//list->at(3).texture = { rectTexture.RB.x, rectTexture.RB.y }; // p4-RB

		if (0)
		{
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
		}
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
	Box_<T> hitbox;
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