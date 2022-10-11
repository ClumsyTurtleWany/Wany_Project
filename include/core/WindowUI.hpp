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

public:
	RECT getClientRect();
	float getClientWidth();
	float getClientHeight();
	Vector2f getClientCenterPos();
	void enableResize();
	void disableResize();
	
public:
	virtual bool run();
	virtual bool resize();
	virtual bool enableFullScreen();
	virtual bool disableFullScreen();
	
public:
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
public:
	WindowUI();
};

