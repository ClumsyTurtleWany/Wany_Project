#pragma once

// WinAPI
#include <windows.h>
#pragma comment(lib, "winmm.lib") // timeGetTime

// Direct X
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#include <d3dcompiler.h> // D3DCompileFromFile
#pragma comment(lib, "d3dCompiler.lib")

// Direct X -> Texture Tool Kit
#include "DXTK/WICTextureLoader.h"
#include "DXTK/DDSTextureLoader.h"
#pragma comment(lib, "DirectXTK.lib")

// STL
#include <vector>
#include <string>
#include <map>

// Geometry
//#include "Vertex.hpp"
#include "Rect.hpp"
#include "Cube.hpp"
#include "Vector.hpp"
#include "Circle.hpp"

enum class Texture_Key
{
	World,
	Player,
	Npc,
	Obstacle,
};

Texture_Key operator++(Texture_Key& _key)
{
	return _key == Texture_Key::Obstacle ? Texture_Key::World : Texture_Key{ ++_key };
}

template <class T>
class BaseSingleton
{
private:
	static T* instance;

protected:
	BaseSingleton() {};
	virtual ~BaseSingleton()
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
T* BaseSingleton<T>::instance = nullptr;