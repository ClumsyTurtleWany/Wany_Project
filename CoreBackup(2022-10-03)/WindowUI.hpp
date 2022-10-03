#pragma once
#include "Define.hpp"

class WindowUI
{
public:
	HINSTANCE	hInstance;
	HWND		hWnd;

	RECT clientRect;
	
public:
	BOOL initInstance(const WCHAR* _title, UINT _width, UINT _height);
	ATOM MyRegisterClass();
	bool createWindow(HINSTANCE _hInstance, const WCHAR* _title, UINT _width, UINT _height);
	RECT getClientRect();

public:
	virtual bool run();

public:
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
public:
	WindowUI();
};

