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

void Skill::updateShader()
{
	Rect_<float> rectNDC;
	rectNDC = ScreenToNDC();

	if (renderCamera != nullptr)
	{
		float magnification_width = mapWidth / renderCamera->getWidth();
		float magnification_Height = mapHeight / renderCamera->getHeight();
		rectNDC.LT.x *= magnification_width;
		rectNDC.LT.y *= magnification_Height;
		rectNDC.RB.x *= magnification_width;
		rectNDC.RB.y *= magnification_Height;
	}
	//rectNDC = ScreenToCamera();

	// Vectex List
	std::vector<Vertex>* list = pShader->getVertexList();
	list->at(0).pos = { rectNDC.LT.x, rectNDC.LT.y, 0.0f };
	list->at(1).pos = { rectNDC.RB.x, rectNDC.LT.y, 0.0f };
	list->at(2).pos = { rectNDC.LT.x, rectNDC.RB.y, 0.0f };
	list->at(3).pos = { rectNDC.RB.x, rectNDC.RB.y, 0.0f };
}

void Skill::setCamera(Camera* _camera)
{
	renderCamera = _camera;
}
