#pragma once
#include "Define.hpp"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")


// Direct X 2D�� ��� ���. DirectWrite ���� Ưȭ ���. 
// �ؽ�Ʈ, ��Ʈ�� ���õ� ����� �� ���⿡ ��� ����.
// Font Collention -> Font Family -> Font/Font Face ������ ������ �� ����.
// ���� ��� ������ -> �ҳ�Ÿ ���� -> �ҳ�Ÿ ���� ���踦 ������.
// gdi -> gdiplus -> directX 2D -> directX 3D ������ ������ ��. (���� ����� �����ؼ� ������ ����)
// 3D �׷��ȿ��� winAPI ��� �Ұ�.


// ��Ʈ�� ������� �ǽð� ���� �Ұ���. �����̶� ���ڴ� ����.
class DXWriter
{
public:
	ID2D1Factory*			m_pd2dFactory;
	IDWriteFactory*			m_pDWriteFactory;
	ID2D1RenderTarget*		m_pd2dRenderTarget; // ���� ������ �ʰ� 3D Device���� �����ͼ� ���.
	IDWriteTextFormat*		m_pTextFormat;
	ID2D1SolidColorBrush*	m_pTextColor;	// ���� ���� �귯��

	std::wstring			m_strDefault;

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();

public:
	bool setBuffer(IDXGISurface* _dxgiSurface);
	void setString(std::wstring _str);
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
	rst = m_pDWriteFactory->CreateTextFormat(
		L"���", //L"Gabriola ", 
		NULL, 
		DWRITE_FONT_WEIGHT_NORMAL, 
		DWRITE_FONT_STYLE_NORMAL, 
		DWRITE_FONT_STRETCH_NORMAL,
		20,
		L"ko-kr", // ���� ��Ʈ�� L"en-us"
		&m_pTextFormat);

	// ��Ʈ�� ������� �ǽð� ���� �Ұ���. �����̶� ���ڴ� ����.

	if (FAILED(rst))
	{
		return false;
	}

	m_strDefault = L"DEFAULT";

	return true; 
};

bool DXWriter::frame() 
{
	return true; 
};

bool DXWriter::render() 
{ 
	m_pd2dRenderTarget->BeginDraw();
	
	// render�� �ݵ�� begin�� end ���̿� �־�� ��.
	D2D1_RECT_F rt = { 100, 100, 300, 300 };
	m_pTextColor->SetColor({ 1, 0, 0, 1 });
	m_pTextColor->SetOpacity(1); // 0�� ����� ���� ��������. 0 ~ 1
	m_pd2dRenderTarget->DrawText(m_strDefault.c_str(), m_strDefault.size(), m_pTextFormat, rt, m_pTextColor);


	m_pd2dRenderTarget->EndDraw();
	return true; 
};

bool DXWriter::release() 
{ 
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
	// 3D -> 2D �����ϴ� ���.
	// IDXGISurface* dxgiSurface,
	// D2D1_RENDER_TARGET_PROPERTIES& renderTargetProperties,
	// ID2D1RenderTarget** renderTarget

	D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties;
	ZeroMemory(&renderTargetProperties, sizeof(renderTargetProperties));
	renderTargetProperties.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	renderTargetProperties.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED); // 3D�� ��� ����ִ��� ���� Unknown.
	renderTargetProperties.dpiX = 96.0f; // inch �� �ȼ��� ���. ������ 96���� ������ ����.
	renderTargetProperties.dpiY = 96.0f; // inch �� �ȼ��� ���. ������ 96���� ������ ����.
	renderTargetProperties.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	renderTargetProperties.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

	// �߿�!
	// CreateDxgiSurfaceRenderTarget �޼ҵ�� DXGI ȭ�鿡 �������ϴ� ���� Ÿ���� �����ϸ� �ݵ�� Direct3D ����̽���
	// �����ÿ� �ݵ�� ������ ���� �÷��׸� �����ؾ� �Ѵ�. Device -> D3D11CreateDevice �� �÷���, DXDevice
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