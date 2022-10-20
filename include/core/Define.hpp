#pragma once

// WinAPI
#include <windows.h>
#pragma comment(lib, "winmm.lib") // timeGetTime

#include <cstdlib> // srand
#include <ctime> // time

extern class WindowUI* g_pWindow;

#define CoreMode
#define DEBUG_DISPLAY

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