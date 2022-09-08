#pragma once
#include "GameCore.hpp"
#include "DXShader.hpp"
#include "DXSamplerState.hpp"
#include "DXShaderManager.hpp"


enum class testKey
{
	Key1,
	Key2,
	Key3
};
//C:\Users\kgca4108\Documents\Visual Studio 2019\My Exported Templates\CoreTestTemplate_0.zip
class Sample : public GameCore
{
public:
	DXShader testShader;
	DXTexture testTexture;

public:
	bool initialize() override;
	bool frame() override;
	bool render() override;
	bool release() override;
};