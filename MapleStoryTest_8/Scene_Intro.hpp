#pragma once
#include "Scene.hpp"
#include "Effect.hpp"

class Scene_Intro : public Scene
{
private:
	Effect* introEffect;

public:
	Scene_Intro(MapleStory* _game);

public:
	virtual bool initialize() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};