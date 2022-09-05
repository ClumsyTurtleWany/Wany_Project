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
	// Direct X 8 버전 Input 생성.
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
		// 키보드 생성
		rst = m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDeviceKeyboard, NULL);
		if (FAILED(rst))
		{
			return false;
		}

		// 키보드 데이터 형식 설정.
		rst = m_pDeviceKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(rst))
		{
			return false;
		}
		
		// 키보드 동작 설정
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
		// 백그라운드 액세스 권한이 허가되면 할당된 윈도우가 활성화 윈도우가 아닌 경우에서도 언제라도 장치를 취득할 수 있다.
		// 응용프로그램이 활성화된 여부에 상관없이 입력장치의 사용이 가능하다.
		// DISCL_FOREGROUND
		// Foreground 액세스가 부여되면 할당된 윈도우가 백그라운드로 이동할 때 장치는 자동적으로 릴리즈 되며 
		// 응용프로그램이 활성화 중일 경우에 입력장치들 사용할 수 있다.
		// DISCL_EXCLUSIVE
		// 배타적 액세스 권한이 주어지면 장치가 취득되고 있는 동안 장치의 다른 인스턴스는 그 장치의 베타 액세스 권한을 취득할 수 없다.
		// DISCL_NONEXCLUSIVE
		// 응용프로그램은 비 배타적 액세스 권한을 요구한다.장치에 대한 액세스 권한은 같은 장치에 액세스 하고 있는 
		// 다른 응용프로그램을 방해하지 않는다.
		// DISCL_NOWINKEY
		// Microsoft Windows® 키를 무효로 한다.이 플래그를 설정 하면 사용자는 잘못해 응용프로그램을 종료하는 것이 없어진다.

		

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
		// 마우스 생성
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

		// 마우스 동작 설정
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