#pragma once

// WinAPI
#pragma comment(lib, "Ws2_32.lib") 
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h>

#include <windows.h> // windows.h �� WinSock2 ���� �߿���. WinSock2�� ���� Include �ϰ� WinSock2�� �ؾ� ���� �۵��� ��.
#pragma comment(lib, "winmm.lib") // timeGetTime

#include <cstdlib> // srand
#include <ctime> // time

#define DEBUG_DISPLAY

// Direct X
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#include <d3dcompiler.h> // D3DCompileFromFile
#pragma comment(lib, "d3dCompiler.lib")

#include <wrl.h> // Microsoft::WRL::ComPtr
using namespace Microsoft::WRL;

// STL
#include <vector>
#include <string>
#include <map>
#include <filesystem> // c++ 17 std
//#include <fstream>

// Shape
#include "Vertex.hpp"
#include "Rect.hpp"
#include "Circle.hpp"
#include "Box.hpp"

// Design Pattern
template <class T>
class Singleton
{
private:
	static T* instance;

protected:
	Singleton() {};
	virtual ~Singleton()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

public:
	static T* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new T;
		}
		return instance;
	}
};

template <class T>
T* Singleton<T>::instance = nullptr;


// FBX SDK
// 1. https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2020-2-1
// 2. Windows -> FBX SDK 2020.2.1 VS2019
// 3. Copy include, lib to project (program files//autodesk//fbx//fbxsdk//2020.2.1//include, lib
//