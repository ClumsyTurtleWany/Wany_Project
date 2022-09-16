#pragma once

enum class KeyState
{
	Free,
	Down,
	Up,
	Push,
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
	GetCursorPos(&m_ptPos); // ȭ�� ��ǥ�� �� ���콺 Ŀ�� ��ġ
	ScreenToClient(hWnd, &m_ptPos); // Ŭ���̾�Ʈ ��ǥ�� ����.

	for (int key = 0; key < 256; key++)
	{
		SHORT state = GetAsyncKeyState(key); // �񵿱� Ű ����
		if (state & 0x8000) // 1000 0000 0000 0000 �ֻ��� ��Ʈ�� �������� Ȯ��
		{
			if ((dwKeyState[key] == KeyState::Free) || (dwKeyState[key] == KeyState::Up))
			{
				dwKeyState[key] = KeyState::Push;
			}
			else
			{
				dwKeyState[key] = KeyState::Hold;
			}
		}
		else
		{
			if ((dwKeyState[key] == KeyState::Push) || (dwKeyState[key] == KeyState::Hold))
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