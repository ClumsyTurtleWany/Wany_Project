#pragma once
#include "Scene.hpp"
#include "Effect.hpp"

class Scene_Title : public Scene
{
private:
	Effect* titleEffect;
	FMODSound* BGM;

public:
	Scene_Title(MapleStory* _game);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};