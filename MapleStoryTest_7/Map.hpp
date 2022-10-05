#pragma once
#include "Object.hpp"
#include "DXShaderBorderManager.hpp"
#include "QuadTree.hpp"
#include "Camera.hpp"
#include "MapObject.hpp"
#include "FMODSoundManager.hpp"

class Map : public object2D<float>
{
private:
	//SpaceDivision* collisionMap;
	QuadTree<float>* collisionMap;
	FMODSound* BGM;
	Vector2f currentUserPos;

public:
	std::vector<MapObject*> mapObjectList;

public:
	Map();
	Map(const Rect2f& _rect);
	virtual ~Map();

public:
	void addMapObject(MapObject* _obj);
	void addObject(object2D<float>* _obj);
	bool Collision(object2D<float>* _src, std::vector<object2D<float>*>* _dst, std::vector<Rect_<float>>* _dstSection = nullptr);
	bool CollisionMapObject(object2D<float>* _obj, MapObjectType _targetType, std::vector<object2D<float>*>* _dst = nullptr, std::vector<Rect_<float>>* _dstSection = nullptr);
	void updateDynamicObject();
	void setBGM(FMODSound* _bgm);

public:
	virtual void updateShader() override;
	virtual void updateShaderCamera() override;

public:
	virtual bool initialize() override;
	virtual bool frame(float _dt) override;
	virtual bool render() override;
	virtual bool release() override;

};