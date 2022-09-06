#pragma once
#include "Define.hpp"

enum class KeyState
{
	Free,
	Down,
	Up,
	Hold
};

// 교재 9강에 Direct Input 이 있으나 여기서는 window 함수 사용 했음. 나중에 바꿀 수 있을지도?
class Input : public Singleton<Input>
{
private:
	HWND		hWnd;

public:
	KeyState dwKeyState[256]; // mouse 버튼 + keyboard 버튼
	POINT m_ptPos; // mouse position

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();

public:
	KeyState getKey(DWORD _key);
	void setWndHandle(HWND _hWnd);
	
};
