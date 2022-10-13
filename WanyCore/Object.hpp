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
	float alphaVal = 1.0f;
	float mapWidth = 0.0f;
	float mapHeight = 0.0f;

	bool filpSpriteHorizontal = false;
	bool filpSpriteVertical = false;

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

	void moveCenterTo(Vector2D_<T> _pos)
	{
		Vector2D_<T> offset;
		offset.x = _pos.x - shape.cx();
		offset.y = _pos.y - shape.cy();
		this->shape.offset(offset);
	}

	void setCamera(Camera* _camera)
	{
		renderCamera = _camera;
	}

	void setAlpha(float _alpha)
	{
		alphaVal = _alpha;
	}

	Circle_<T> getCircle()
	{
		return Circle_<T>(this->shape.center(), this->shape.length() / 2.0f);
	}

	Rect_<T> ScreenToNDC_noCamera()
	{
		RECT clientRect = g_pWindow->getClientRect();
		float clientWidth = static_cast<float>(clientRect.right - clientRect.left); // clientRectWidth;
		float clientHeight = static_cast<float>(clientRect.bottom - clientRect.top); // clientRectHeight;
		float mapWidth_Half = clientWidth * 0.5f;
		float mapHeight_Half = clientHeight * 0.5f;

		Rect_<T> rectNDC;
		rectNDC.LT.x = (shape.LT.x - mapWidth_Half) / mapWidth_Half;
		rectNDC.LT.y = -(shape.LT.y - mapHeight_Half) / mapHeight_Half;
		rectNDC.RB.x = (shape.RB.x - mapWidth_Half) / mapWidth_Half;
		rectNDC.RB.y = -(shape.RB.y - mapHeight_Half) / mapHeight_Half;

		return rectNDC;
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

	void flipTexture(bool _horizontal, bool _vertical = false)
	{
		if (_horizontal)
		{
			std::vector<Vertex>* list = pShader->getVertexList();
			Vector2f LT = list->at(0).texture;
			Vector2f RT = list->at(1).texture;
			Vector2f LB = list->at(2).texture;
			Vector2f RB = list->at(3).texture;
			list->at(0).texture = RT; //{ 0.0f, 0.0f }; // LT
			list->at(1).texture = LT; //{ 1.0f, 0.0f }; // RT
			list->at(2).texture = RB; //{ 0.0f, 1.0f }; // LB
			list->at(3).texture = LB; //{ 1.0f, 1.0f }; // RB
		}

		if (_vertical)
		{
			std::vector<Vertex>* list = pShader->getVertexList();
			Vector2f LT = list->at(0).texture;
			Vector2f RT = list->at(1).texture;
			Vector2f LB = list->at(2).texture;
			Vector2f RB = list->at(3).texture;
			list->at(0).texture = LB;
			list->at(1).texture = RB;
			list->at(2).texture = LT;
			list->at(3).texture = RT;
		}
	}

	void flipSprite(bool _horizontal, bool _vertical = false)
	{
		if (_horizontal == true)
		{
			filpSpriteHorizontal = !filpSpriteHorizontal;
		}

		if (_vertical == true)
		{
			filpSpriteVertical = !filpSpriteVertical;
		}
	}

	void flipSpriteHorizontal()
	{
		filpSpriteHorizontal = !filpSpriteHorizontal;		
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
		Rect_<float> rectNDC;
		rectNDC = ScreenToNDC_noCamera(); //ScreenToNDC();
		

		//rectNDC = ScreenToCamera();

		// Vectex List
		std::vector<Vertex>*list = pShader->getVertexList();
		list->at(0).pos = { rectNDC.LT.x, rectNDC.LT.y, 0.0f };
		list->at(1).pos = { rectNDC.RB.x, rectNDC.LT.y, 0.0f };
		list->at(2).pos = { rectNDC.LT.x, rectNDC.RB.y, 0.0f };
		list->at(3).pos = { rectNDC.RB.x, rectNDC.RB.y, 0.0f };

		list->at(0).color.w = alphaVal;
		list->at(1).color.w = alphaVal;
		list->at(2).color.w = alphaVal;
		list->at(3).color.w = alphaVal;

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
			
			if (filpSpriteHorizontal)
			{
				Vector2f LT = list->at(0).texture;
				Vector2f RT = list->at(1).texture;
				Vector2f LB = list->at(2).texture;
				Vector2f RB = list->at(3).texture;
				list->at(0).texture = RT; //{ 0.0f, 0.0f }; // LT
				list->at(1).texture = LT; //{ 1.0f, 0.0f }; // RT
				list->at(2).texture = RB; //{ 0.0f, 1.0f }; // LB
				list->at(3).texture = LB; //{ 1.0f, 1.0f }; // RB
			}

			if (filpSpriteVertical)
			{
				Vector2f LT = list->at(0).texture;
				Vector2f RT = list->at(1).texture;
				Vector2f LB = list->at(2).texture;
				Vector2f RB = list->at(3).texture;
				list->at(0).texture = LB;
				list->at(1).texture = RB;
				list->at(2).texture = LT;
				list->at(3).texture = RT;
			}
		}
			
		Matrix<float> s = Make3DMatrix_Scale(0.5f, 0.5f, 0.0f);
		Matrix<float> r = Make3DMatrix_RotationZ(DegreeToRadian(0));
		Matrix<float> t = Make3DMatrix_Translation(0.1f, 0.1f, 0.0f);
		Matrix<float> srt = s * r * t;
		for (int i = 0; i < list->size(); i++)
		{
			Vector4f temp = Vector4f(list->at(i).pos.x, list->at(i).pos.y, list->at(i).pos.z, 1.0f);
			temp = temp * srt;
			list->at(i).pos = Vector3f(temp.x, temp.y, temp.z);
		}

	}

	// 2022-09-22 Test
	virtual void updateShaderCamera()
	{
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

		// Vectex List
		std::vector<Vertex>* list = pShader->getVertexList();
		list->at(0).pos = { rectNDC.LT.x, rectNDC.LT.y, 0.0f };
		list->at(1).pos = { rectNDC.RB.x, rectNDC.LT.y, 0.0f };
		list->at(2).pos = { rectNDC.LT.x, rectNDC.RB.y, 0.0f };
		list->at(3).pos = { rectNDC.RB.x, rectNDC.RB.y, 0.0f };

		float cosAngleVal = cos(DegreeToRadian(angle));
		float sinAngleVal = sin(DegreeToRadian(angle));

		Vector3f center;
		center.x = (list->at(0).pos.x + list->at(1).pos.x) / 2.0f;
		center.y = (list->at(0).pos.y + list->at(2).pos.y) / 2.0f;
		
		Vector3f centerMoved;
		centerMoved = list->at(0).pos - center;
		Vector3f rstRotation;
		rstRotation.x = centerMoved.x * cosAngleVal - centerMoved.y * sinAngleVal;
		rstRotation.y = centerMoved.x * sinAngleVal + centerMoved.y * cosAngleVal;
		list->at(0).pos = rstRotation + center;
		
		centerMoved = list->at(1).pos - center;
		rstRotation.x = centerMoved.x * cosAngleVal - centerMoved.y * sinAngleVal;
		rstRotation.y = centerMoved.x * sinAngleVal + centerMoved.y * cosAngleVal;
		list->at(1).pos = rstRotation + center;

		centerMoved = list->at(2).pos - center;
		rstRotation.x = centerMoved.x * cosAngleVal - centerMoved.y * sinAngleVal;
		rstRotation.y = centerMoved.x * sinAngleVal + centerMoved.y * cosAngleVal;
		list->at(2).pos = rstRotation + center;

		centerMoved = list->at(3).pos - center;
		rstRotation.x = centerMoved.x * cosAngleVal - centerMoved.y * sinAngleVal;
		rstRotation.y = centerMoved.x * sinAngleVal + centerMoved.y * cosAngleVal;
		list->at(3).pos = rstRotation + center;


		
		list->at(0).color = { 1.0f, 1.0f, 1.0f, alphaVal };
		list->at(1).color = { 1.0f, 1.0f, 1.0f, alphaVal };
		list->at(2).color = { 1.0f, 1.0f, 1.0f, alphaVal };
		list->at(3).color = { 1.0f, 1.0f, 1.0f, alphaVal };

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
			
			if (filpSpriteHorizontal)
			{
				Vector2f LT = list->at(0).texture;
				Vector2f RT = list->at(1).texture;
				Vector2f LB = list->at(2).texture;
				Vector2f RB = list->at(3).texture;
				list->at(0).texture = RT; //{ 0.0f, 0.0f }; // LT
				list->at(1).texture = LT; //{ 1.0f, 0.0f }; // RT
				list->at(2).texture = RB; //{ 0.0f, 1.0f }; // LB
				list->at(3).texture = LB; //{ 1.0f, 1.0f }; // RB
			}

			if (filpSpriteVertical)
			{
				Vector2f LT = list->at(0).texture;
				Vector2f RT = list->at(1).texture;
				Vector2f LB = list->at(2).texture;
				Vector2f RB = list->at(3).texture;
				list->at(0).texture = LB;
				list->at(1).texture = RB;
				list->at(2).texture = LT;
				list->at(3).texture = RT;
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