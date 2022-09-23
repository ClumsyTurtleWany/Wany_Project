#include "Skill.hpp"

Skill::Skill()
{
}

Skill::Skill(const Rect2f& _rect)
{
	shape = _rect;
}

Skill::~Skill()
{
}

void Skill::setCamera(Camera* _camera)
{
	renderCamera = _camera;
}
