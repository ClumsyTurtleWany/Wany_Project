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
// 3D �׷��ȿ��� WinAPI ��� �Ұ�.

// �ظ��ϸ� DrawText�� ��� ���ϴ°� ����. ���������� �ֹ�. 
// ���� ���ӿ��� ��������� sprite�� �̿��Ͽ� ���� �̹����� ��¸� ���ִ� ��찡 ����.
// ä���̳� ��¿ �� ���� ���(���� �̹����� ���� ���) ����Ѵ�.
class DXWriter : public Singleton<DXWriter>
{
public:
	ID2D1Factory*			m_pd2dFactory;
	IDWriteFactory*			m_pDWriteFactory;
	ID2D1RenderTarget*		m_pd2dRenderTarget; // ���� ������ �ʰ� 3D Device���� �����ͼ� ���.
	IDWriteTextFormat*		m_pTextFormat; // ����(Text)�� �ٲ� �� ������ ��Ʈ�� ũ��� ���� �Ұ�, �����̳� ��ġ�� ���� ����.
	ID2D1SolidColorBrush*	m_pTextColor;	// ���� ���� �귯��

	std::wstring			m_strDefault;

	IDWriteTextLayout* m_pTextLayout; // ����(Text)�� ���ٲٴ� ��� ��Ʈ�� ũ�� ���� ��� ���� ���� ����.

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

