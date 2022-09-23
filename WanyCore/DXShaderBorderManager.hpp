#pragma once
#include "DXShaderBorder.hpp"
#include "Camera.hpp"

#define BORDER_COLOR_RED Vector4f(1.0f, 0.0f, 0.0f, 1.0f)
#define BORDER_COLOR_GREEN Vector4f(0.0f, 1.0f, 0.0f, 1.0f)
#define BORDER_COLOR_BLUE Vector4f(0.0f, 0.0f, 1.0f, 1.0f)
#define BORDER_COLOR_YELLOW Vector4f(1.0f, 1.0f, 0.0f, 1.0f)

class DXShaderBorderManager : public Singleton< DXShaderBorderManager>
{
private:
	friend class Singleton<DXShaderBorderManager>;

	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

	DXShaderBorder* m_pBorderShader = nullptr;
	Camera* renderCamera = nullptr;

	Vector2f mapSize;

private:
	DXShaderBorderManager() {};
	~DXShaderBorderManager() { release(); };

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
	void setCamera(Camera* _camera);
	void setMapSize(Vector2f _size);
	bool drawBorder(const Rect2f& _rect, const Vector4f& _color);

public:
	bool initialize();
	bool frame();
	bool render();
	bool release();
};

// DrawBorder(const Rect2f& _rect, const Vector4f& _color)
#define DrawBorder(_rect, _color) DXShaderBorderManager::getInstance()->drawBorder(_rect, _color)