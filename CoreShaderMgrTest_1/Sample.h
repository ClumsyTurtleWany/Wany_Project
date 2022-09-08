#pragma once
#include "GameCore.hpp"

#define RSRC_BACKGROUND L"../../resource/KGCABK.bmp"
#define RSRC_CHARATER L"../../resource/bitmap1.bmp"
#define RSRC_CHARATER_MASK L"../../resource/bitmap2.bmp"
//C:\Users\kgca4108\Documents\Visual Studio 2019\My Exported Templates\CoreTestTemplate_0.zip
class Sample : public GameCore
{
public:
	DXShader* Background;
	DXShader* user;

public:
	bool initialize() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};