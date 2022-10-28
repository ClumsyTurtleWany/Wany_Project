#pragma once
#include "GameCore.hpp"
#include "NewObject.hpp"
#include "DebugCamera.hpp"
#include "DXTextureRenderTarget.hpp"
#include "FBXLoader.hpp"

#define CHARACTER_DIR L"../resource/MapleStory/0.bmp"
#define MAP_DIR L"../../resource/map/002.jpg"

//C:\Users\kgca4108\Documents\Visual Studio 2019\My Exported Templates\CoreTestTemplate_0.zip
class Sample : public GameCore
{
public:
	Plane3D* pObject = nullptr;
	Cube3D* pBoxObject = nullptr;
	Map3D* pWorldMap = nullptr;
	DebugCamera* renderCamera = nullptr;
	D3D11_VIEWPORT ViewPort[4];
	Camera* ViewPortCamera[4];
	DXTextureRenderTarget textureRenderTarget;

	FBXLoader fbxLoader;

public:
	bool initialize() override;
	bool frame() override;
	bool render() override;
	bool release() override;
	
public:
	bool resize() override;
};