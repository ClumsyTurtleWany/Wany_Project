#pragma once
#include "Define.hpp"

enum class KeyState
{
	Free,
	Down,
	Up,
	Hold
};

// ���� 9���� Direct Input �� ������ ���⼭�� window �Լ� ��� ����. ���߿� �ٲ� �� ��������?
class Input : public Singleton<Input>
{
private:
	HWND		hWnd;

public:
	KeyState dwKeyState[256]; // mouse ��ư + keyboard ��ư
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
