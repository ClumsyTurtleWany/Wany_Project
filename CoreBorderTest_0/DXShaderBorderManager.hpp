#pragma once
#include "DXShaderBorder.hpp"

#define BORDER_COLOR_RED Vector4f(1.0f, 0.0f, 0.0f, 1.0f)
#define BORDER_COLOR_GREEN Vector4f(0.0f, 1.0f, 0.0f, 1.0f)
#define BORDER_COLOR_BLUE Vector4f(0.0f, 0.0f, 1.0f, 1.0f)

class DXShaderBorderManager : public Singleton< DXShaderBorderManager>
{
private:
	friend class Singleton<DXShaderBorderManager>;

	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

	DXShaderBorder* m_pBorderShader = nullptr;

private:
	DXShaderBorderManager() {};
	~DXShaderBorderManager() { release(); };

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
	bool drawBorder(const Rect2f& _rect, const Vector4f& _color);

public:
	bool initialize();
	bool frame();
	bool render();
	bool release();
};