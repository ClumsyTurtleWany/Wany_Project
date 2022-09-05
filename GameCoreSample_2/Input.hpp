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
	void setWndHandle(HWND _hWnd)
	{
		hWnd = _hWnd;
	}
};

KeyState Input::getKey(DWORD _key)
{
	return dwKeyState[_key];
}

bool Input::initialize()
{
	ZeroMemory(&dwKeyState, sizeof(DWORD) * 256);

	return true;
}

bool Input::frame()
{
	GetCursorPos(&m_ptPos); // 화면 좌표계 상 마우스 커서 위치
	ScreenToClient(hWnd, &m_ptPos); // 클라이언트 좌표로 변경.

	for (int key = 0; key < 256; key++)
	{
		SHORT state = GetAsyncKeyState(key); // 비동기 키 상태
		if (state & 0x8000) // 1000 0000 0000 0000 최상위 비트로 눌러졌나 확인
		{
			if ((dwKeyState[key] == KeyState::Free) || (dwKeyState[key] == KeyState::Up))
			{
				dwKeyState[key] = KeyState::Down;
			}
			else
			{
				dwKeyState[key] = KeyState::Hold;
			}
		}
		else
		{
			if ((dwKeyState[key] == KeyState::Down) || (dwKeyState[key] == KeyState::Hold))
			{
				dwKeyState[key] = KeyState::Up;
			}
			else
			{
				dwKeyState[key] = KeyState::Free;
			}
		}
	}
	return true;
}

bool Input::render()
{

	return true;
}

bool Input::release()
{

	return true;
}