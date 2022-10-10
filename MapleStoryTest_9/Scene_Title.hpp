#pragma once
#include "Scene.hpp"
#include "Effect.hpp"

class Scene_Title : public Scene
{
private:
	object2D<float>* titleBackground;
	FMODSound* BGM;

	float alpha = 1.0f;

public:
	Scene_Title(MapleStory* _game);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};