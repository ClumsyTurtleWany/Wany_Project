#pragma once
#include "Define.hpp"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")


// Direct X 2D의 기능 사용. DirectWrite 글자 특화 기능. 
// 텍스트, 폰트와 관련된 기능은 다 여기에 들어 있음.
// Font Collention -> Font Family -> Font/Font Face 순으로 나뉘어 져 있음.
// 예를 들면 현대차 -> 소나타 종류 -> 소나타 같은 관계를 형성함.
// gdi -> gdiplus -> directX 2D -> directX 3D 순서로 나오게 됨. (기존 기능은 불편해서 개선에 개선)
// 3D 그래픽에는 WinAPI 사용 불가.

// 왠만하면 DrawText는 사용 안하는게 좋다. 성능저하의 주범. 
// 보통 게임에서 글자출력은 sprite를 이용하여 글자 이미지로 출력만 해주는 경우가 많음.
// 채팅이나 어쩔 수 없는 경우(글자 이미지가 없는 경우) 사용한다.
class DXWriter : public Singleton<DXWriter>
{
public:
	ID2D1Factory*			m_pd2dFactory;
	IDWriteFactory*			m_pDWriteFactory;
	ID2D1RenderTarget*		m_pd2dRenderTarget; // 직접 만들지 않고 3D Device에서 가져와서 사용.
	IDWriteTextFormat*		m_pTextFormat; // 글자(Text)를 바꿀 수 있지만 폰트와 크기는 변경 불가, 색상이나 위치는 변경 가능.
	ID2D1SolidColorBrush*	m_pTextColor;	// 색상 관련 브러쉬

	std::wstring			m_strDefault;

	IDWriteTextLayout* m_pTextLayout; // 글자(Text)를 못바꾸는 대신 폰트나 크기 색상 등등 전부 변경 가능.

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();

public:
	bool setBuffer(IDXGISurface* _dxgiSurface);
	void setString(std::wstring _str);
	bool draw(int _x, int _y, std::wstring _str, D2D1_COLOR_F _color);
};

bool DXWriter::initialize() 
{ 
	HRESULT rst;
	rst = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pd2dFactory);
	if (FAILED(rst))
	{
		return false;
	}

	rst = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&m_pDWriteFactory);
	if (FAILED(rst))
	{
		return false;
	}

	// m_pDWriteFactory->CreateTextFormat
	// WCHAR const* fontFamilyName,
	// IDWriteFontCollection* fontCollection,
	//	DWRITE_FONT_WEIGHT fontWeight,
	//	DWRITE_FONT_STYLE fontStyle,
	//	DWRITE_FONT_STRETCH fontStretch,
	//	FLOAT fontSize,
	//	WCHAR const* localeName,
	//	IDWriteTextFormat** textFormat
	// 폰트랑 사이즈는 실시간 변경 불가함. 색상이랑 글자는 가능.
	rst = m_pDWriteFactory->CreateTextFormat(
		L"고딕", //L"Gabriola ", 
		NULL, 
		DWRITE_FONT_WEIGHT_NORMAL, 
		DWRITE_FONT_STYLE_NORMAL, 
		DWRITE_FONT_STRETCH_NORMAL,
		20,
		L"ko-kr", // 영문 폰트면 L"en-us"
		&m_pTextFormat);

	

	if (FAILED(rst))
	{
		return false;
	}

	m_strDefault = L"DEFAULT";
	// 글자가 박혀있어서 글자는 변경 불가능 하다.
	rst = m_pDWriteFactory->CreateTextLayout(
		m_strDefault.c_str(),
		m_strDefault.size(),
		m_pTextFormat,
		1024, 768,
		&m_pTextLayout);

	if (FAILED(rst))
	{
		return false;
	}

	

	return true; 
};

bool DXWriter::frame() 
{
	return true; 
};

bool DXWriter::render() 
{ 
	m_pd2dRenderTarget->BeginDraw();
	
	// render는 반드시 begin과 end 사이에 넣어야 함.
	// Draw
	D2D1_RECT_F rt = { 0, 0, 600, 300 };
	m_pTextColor->SetColor({ 1, 0, 0, 1 });
	m_pTextColor->SetOpacity(1); // 0에 가까울 수록 투명해짐. 0 ~ 1
	m_pd2dRenderTarget->DrawText(m_strDefault.c_str(), m_strDefault.size(), m_pTextFormat, rt, m_pTextColor);

	m_pd2dRenderTarget->EndDraw();
	return true; 
};

bool DXWriter::release() 
{ 
	if (m_pTextLayout != nullptr)
	{
		m_pTextLayout->Release();
		m_pTextLayout = nullptr;
	}

	if (m_pTextColor != nullptr)
	{
		m_pTextColor->Release();
		m_pTextColor = nullptr;
	}
	
	if (m_pDWriteFactory != nullptr)
	{
		m_pDWriteFactory->Release();
		m_pDWriteFactory = nullptr;
	}

	if (m_pd2dRenderTarget != nullptr)
	{
		m_pd2dRenderTarget->Release();
		m_pd2dRenderTarget = nullptr;
	}

	if (m_pd2dFactory != nullptr)
	{
		m_pd2dFactory->Release();
		m_pd2dFactory = nullptr;
	}
	
	return true; 
};

bool DXWriter::setBuffer(IDXGISurface* _dxgiSurface)
{
	// 3D -> 2D 연동하는 기능.
	// IDXGISurface* dxgiSurface,
	// D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties,
	// ID2D1RenderTarget** renderTarget

	D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties;
	ZeroMemory(&renderTargetProperties, sizeof(renderTargetProperties));
	renderTargetProperties.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	renderTargetProperties.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED); // 3D에 어떻게 들어있는지 몰라서 Unknown.
	renderTargetProperties.dpiX = 96.0f; // inch 당 픽셀이 몇개냐. 보통은 96개를 가지고 있음.
	renderTargetProperties.dpiY = 96.0f; // inch 당 픽셀이 몇개냐. 보통은 96개를 가지고 있음.
	renderTargetProperties.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	renderTargetProperties.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

	// 중요!
	// CreateDxgiSurfaceRenderTarget 메소드는 DXGI 화면에 랜더링하는 랜더 타켓을 생성하며 반드시 Direct3D 디바이스를
	// 생성시에 반드시 다음과 같이 플래그를 지정해야 한다. Device -> D3D11CreateDevice 의 플래그, DXDevice
	// UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	// #ifdef _DEBUG 
	// createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	// #endif 
	HRESULT rst = m_pd2dFactory->CreateDxgiSurfaceRenderTarget(_dxgiSurface, renderTargetProperties, &m_pd2dRenderTarget);
	if (FAILED(rst))
	{
		return false;
	}


	m_pd2dRenderTarget->CreateSolidColorBrush(D2D1_COLOR_F({ 0.0f, 0.0f, 0.0f, 1.0f }), &m_pTextColor);

	return true;
}

void DXWriter::setString(std::wstring _str)
{
	m_strDefault = _str;
}

bool DXWriter::draw(int _x, int _y, std::wstring _str, D2D1_COLOR_F _color)
{
	m_pd2dRenderTarget->BeginDraw();

	// render는 반드시 begin과 end 사이에 넣어야 함.
	D2D1_RECT_F rt = { _x, _y, 600, 300 };
	m_pTextColor->SetColor(_color);
	m_pTextColor->SetOpacity(1); // 0에 가까울 수록 투명해짐. 0 ~ 1
	m_pd2dRenderTarget->DrawText(_str.c_str(), _str.size(), m_pTextFormat, rt, m_pTextColor);


	// Draw Layout
	m_pTextLayout->SetFontSize(_x, { 0, (UINT)m_strDefault.size() });
	m_pTextLayout->SetFontStyle(DWRITE_FONT_STYLE_ITALIC, { 0, (UINT)m_strDefault.size() });
	m_pd2dRenderTarget->DrawTextLayout({ 0, 0 }, m_pTextLayout, m_pTextColor);

	m_pd2dRenderTarget->EndDraw();
	return true;
};
