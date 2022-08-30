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

// STL
#include <vector>
#include <string>

// Geometry
#include "Vertex.hpp"
#include "Rect.hpp"
#include "Cube.hpp"
#include "Vector.hpp"
#include "Circle.hpp"