#pragma once
#include "Object.hpp"
#include "Timer.hpp"
#include "DXTextureManager.hpp"
#include "DXShaderBorderManager.hpp"
#include <filesystem>
#include <fstream>

class Effect : public object2D<float>
{
public:
	int state = 0;
	float beforeTime = 0.0f;
	float timeCounter = 0.0f;
	float frameTime = 0.0f;
	float totalTime = 0.0f;

	float lifeTime = 0.0f;

	bool isEnd = false;

	Vector2f pos;
	std::vector<std::wstring> textureKeyList;

public:
	Effect();
	Effect(Effect* _src);
	Effect(const Rect2f& _rect);
	virtual ~Effect();

public:
	virtual bool Load(std::wstring _path);
	virtual bool LoadInfo(std::wstring _path);
	void setPos(Vector2f _pos);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};