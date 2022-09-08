#pragma once
#include "GameCore.hpp"
#include "DXShader.hpp"
#include "DXTextureManager.hpp"

#define RSRC_BACKGROUND L"../../resource/KGCABK.bmp"
#define RSRC_CHARATER L"../../resource/bitmap1.bmp"
#define SHADER_FILE L"../include/core/HLSL/ShapeShader.txt"

//C:\Users\kgca4108\Documents\Visual Studio 2019\My Exported Templates\CoreTestTemplate_0.zip
class Sample : public GameCore
{
public:
	DXShader testShader;

public:
	bool initialize() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};