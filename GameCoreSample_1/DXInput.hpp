#pragma once
#include "Define.hpp"

#include <dinput.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

#define KEY_STATE_COUNT 256
#define SAMPLE_BUFFER_SIZE 16

class DXInput : public Singleton<DXInput>
{
private:
	HINSTANCE				hInstance;
	HWND					hWnd;

	LPDIRECTINPUT8			m_pDirectInput;
	LPDIRECTINPUTDEVICE8	m_pDeviceKeyboard;
	LPDIRECTINPUTDEVICE8	m_pDeviceMouse;
	DIDEVICEOBJECTDATA		m_didod[SAMPLE_BUFFER_SIZE];

	DWORD					m_dwImmediate = false;
	DWORD					m_dwElements;

public:
	BYTE					m_KeyState[KEY_STATE_COUNT];
	BYTE					m_KeyBeforeState[KEY_STATE_COUNT];
	DIMOUSESTATE			m_MouseState;
	DIMOUSESTATE			m_MouseBeforeState;
	

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();

public:
	void setInstance(HINSTANCE _instance)
	{
		hInstance = _instance;
	}

	void setWndHandle(HWND _hWnd)
	{
		hWnd = _hWnd;
	}

	bool keyboardProc();
	bool mouseProc();
	bool postProc();
	bool isKeyDown(DWORD _dwKey);
	bool isKeyUp(DWORD _dwKey);
};

bool DXInput::initialize()
{
	// Direct X 8 ���� Input ����.
	// DirectInput8Create
	// HINSTANCE hinst 
	// DWORD dwVersion
	// REFIID riidltf
	// LPVOID* ppvOut
	// LPUNKNOWN punkOuter
	HRESULT rst = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL);
	if (FAILED(rst))
	{
		return false;
	}

	bool bKeyboard = true;
	if (bKeyboard)
	{
		// Ű���� ����
		rst = m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDeviceKeyboard, NULL);
		if (FAILED(rst))
		{
			return false;
		}

		// Ű���� ������ ���� ����.
		rst = m_pDeviceKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(rst))
		{
			return false;
		}
		
		// Ű���� ���� ����
		rst = m_pDeviceKeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY);
		if (FAILED(rst))
		{
			while (m_pDeviceKeyboard->Acquire() == DIERR_INPUTLOST);
			rst = m_pDeviceKeyboard->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_BACKGROUND | DISCL_NOWINKEY);
			if (FAILED(rst))
			{
				return false;
			}
		}
		// DISCL_BACKGROUND
		// ��׶��� �׼��� ������ �㰡�Ǹ� �Ҵ�� �����찡 Ȱ��ȭ �����찡 �ƴ� ��쿡���� ������ ��ġ�� ����� �� �ִ�.
		// �������α׷��� Ȱ��ȭ�� ���ο� ������� �Է���ġ�� ����� �����ϴ�.
		// DISCL_FOREGROUND
		// Foreground �׼����� �ο��Ǹ� �Ҵ�� �����찡 ��׶���� �̵��� �� ��ġ�� �ڵ������� ������ �Ǹ� 
		// �������α׷��� Ȱ��ȭ ���� ��쿡 �Է���ġ�� ����� �� �ִ�.
		// DISCL_EXCLUSIVE
		// ��Ÿ�� �׼��� ������ �־����� ��ġ�� ���ǰ� �ִ� ���� ��ġ�� �ٸ� �ν��Ͻ��� �� ��ġ�� ��Ÿ �׼��� ������ ����� �� ����.
		// DISCL_NONEXCLUSIVE
		// �������α׷��� �� ��Ÿ�� �׼��� ������ �䱸�Ѵ�.��ġ�� ���� �׼��� ������ ���� ��ġ�� �׼��� �ϰ� �ִ� 
		// �ٸ� �������α׷��� �������� �ʴ´�.
		// DISCL_NOWINKEY
		// Microsoft Windows�� Ű�� ��ȿ�� �Ѵ�.�� �÷��׸� ���� �ϸ� ����ڴ� �߸��� �������α׷��� �����ϴ� ���� ��������.

		

		if (!m_dwImmediate)
		{
			DIPROPDWORD DirectInputPropDword;
			DirectInputPropDword.diph.dwSize		= sizeof(DIPROPDWORD);
			DirectInputPropDword.diph.dwHeaderSize	= sizeof(DIPROPHEADER);
			DirectInputPropDword.diph.dwObj			= 0;
			DirectInputPropDword.diph.dwHow			= DIPH_DEVICE;
			DirectInputPropDword.dwData				= SAMPLE_BUFFER_SIZE;

			rst = m_pDeviceKeyboard->SetProperty(DIPROP_BUFFERSIZE, &DirectInputPropDword.diph);
			if (FAILED(rst))
			{
				return false;
			}
		}

		while (m_pDeviceKeyboard->Acquire() == DIERR_INPUTLOST);
	}

	bool bMouse = true;
	if (bMouse)
	{
		// ���콺 ����
		rst = m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDeviceMouse, NULL);
		if (FAILED(rst))
		{
			return false;
		}

		rst = m_pDeviceMouse->SetDataFormat(&c_dfDIMouse);
		if (FAILED(rst))
		{
			return false;
		}

		// ���콺 ���� ����
		rst = m_pDeviceMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		if (FAILED(rst))
		{
			while (m_pDeviceMouse->Acquire() == DIERR_INPUTLOST);
			rst = m_pDeviceMouse->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_BACKGROUND);
			if (FAILED(rst))
			{
				return false;
			}
		}

		while (m_pDeviceMouse->Acquire() == DIERR_INPUTLOST);
	}

	m_dwElements = 0;
	memset(&m_KeyBeforeState, 0, sizeof(BYTE) * KEY_STATE_COUNT);
	memset(&m_MouseBeforeState, 0, sizeof(DIMOUSESTATE));

	return true;
}

bool DXInput::frame()
{

	keyboardProc();
	mouseProc();

	return true;
}

bool DXInput::render()
{

	postProc();
	return true;
}

bool DXInput::release()
{
	if (m_pDeviceKeyboard != nullptr)
	{
		m_pDeviceKeyboard->Unacquire();
		m_pDeviceKeyboard->Release();
		m_pDeviceKeyboard = nullptr;
	}

	if (m_pDeviceMouse != nullptr)
	{
		m_pDeviceMouse->Unacquire();
		m_pDeviceMouse->Release();
		m_pDeviceMouse = nullptr;
	}

	if (m_pDirectInput != nullptr)
	{
		m_pDirectInput->Release();
		m_pDirectInput = nullptr;
	}

	return true;
}

bool DXInput::keyboardProc()
{
	if (m_pDeviceKeyboard == nullptr)
	{
		return false;
	}

	HRESULT rst = m_pDeviceKeyboard->Acquire();
	
	if (m_dwImmediate)
	{
		ZeroMemory(m_KeyState, sizeof(BYTE) * KEY_STATE_COUNT);
		//rst = m_pDeviceKeyboard->GetDeviceState(KEY_STATE_COUNT, m_KeyState);
		//if (FAILED(rst))
		if (FAILED(m_pDeviceKeyboard->GetDeviceState(KEY_STATE_COUNT, m_KeyState)))
		{
			while (m_pDeviceKeyboard->Acquire() == DIERR_INPUTLOST)
			{
				m_pDeviceKeyboard->Acquire();
			}
			
			return true;
		}
	}
	else
	{
		//memset(&m_didod, 0, sizeof(DIDEVICEOBJECTDATA) * SAMPLE_BUFFER_SIZE);
		ZeroMemory(&m_didod, sizeof(DIDEVICEOBJECTDATA) * SAMPLE_BUFFER_SIZE);
		m_dwElements = SAMPLE_BUFFER_SIZE;
		rst = m_pDeviceKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_didod, &m_dwElements, 0);
		if (rst != DI_OK)
		{
			m_dwElements = 0;
			rst = m_pDeviceKeyboard->Acquire();
			while (rst == DIERR_INPUTLOST)
			{
				rst = m_pDeviceKeyboard->Acquire();
			}
			return true;
		}
	}

	return true;
}

bool DXInput::mouseProc()
{
	HRESULT rst = m_pDeviceMouse->Acquire();

	ZeroMemory(&m_MouseState, sizeof(DIMOUSESTATE));
	if (m_pDeviceMouse == nullptr)
	{
		return false;
	}

	if (FAILED(m_pDeviceMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState)))
	{
		while (m_pDeviceMouse->Acquire() == DIERR_INPUTLOST)
		{
			m_pDeviceMouse->Acquire();
		}

		return true;
	}

	return true;
}

bool DXInput::isKeyDown(DWORD _dwKey)
{
	if (m_dwImmediate)
	{
		if (m_KeyState[_dwKey] & 0x8000)
		{
			return true;
		}
	}
	else
	{
		for (DWORD i = 0; i < m_dwElements; i++)
		{
			if (m_didod[i].dwOfs == _dwKey && (m_didod[i].dwData & 0x8000))
			{
				return true;
			}
		}
	}
	return false;
}

bool DXInput::isKeyUp(DWORD _dwKey)
{
	return false;
}

bool DXInput::postProc()
{
	memcpy(&m_KeyBeforeState, &m_KeyState, sizeof(BYTE) * KEY_STATE_COUNT);
	memcpy(&m_MouseBeforeState, &m_MouseState, sizeof(DIMOUSESTATE));
	return true;
}