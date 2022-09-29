#include "Input.hpp"


void Input::setWndHandle(HWND _hWnd)
{
	hWnd = _hWnd;
}

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
	std::wstring mousePos = L"Mouse Cursor: " + std::to_wstring(m_ptPos.x) + L", " + std::to_wstring(m_ptPos.y) + L"\n";
	//OutputDebugString(mousePos.c_str());
	return true;
}

bool Input::release()
{

	return true;
}