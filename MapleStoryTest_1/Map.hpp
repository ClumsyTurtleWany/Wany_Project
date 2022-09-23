#pragma once
#include "Object.hpp"
#include "DXShaderBorderManager.hpp"
#include "QuadTree.hpp"
#include "Camera.hpp"
#include "MapObject.hpp"

class Map : public object2D<float>
{
private:
	SpaceDivision* collisionMap;
	std::vector<MapObject*> mapObjectList;

public:
	Map();
	Map(const Rect2f& _rect);
	virtual ~Map();

public:
	void addMapObject(MapObject* _obj);
	void addObject(objectBase* _obj);
	bool Collision(objectBase* _src, std::vector<objectBase*>* _dst, std::vector<Rect_<float>>* _dstSection = nullptr);
	bool CollisionMapObject(object2D<float>* _obj);
	void updateDynamicObject();

public:
	virtual void updateShader() override;
	virtual void updateShaderCamera() override;

public:
	virtual bool initialize() override;
	virtual bool frame(float _dt) override;
	virtual bool render() override;
	virtual bool release() override;

};