#include "NewObject.hpp"

void NewObject::updateShader()
{
	Rect_<float> rectNDC;
	rectNDC = ScreenToNDC_noCamera(); //ScreenToNDC();


	//rectNDC = ScreenToCamera();

	// Vectex List
	std::vector<Vertex>* list = pShader->getVertexList();
	list->at(0).pos = { rectNDC.LT.x, rectNDC.LT.y, 0.0f };
	list->at(1).pos = { rectNDC.RB.x, rectNDC.LT.y, 0.0f };
	list->at(2).pos = { rectNDC.LT.x, rectNDC.RB.y, 0.0f };
	list->at(3).pos = { rectNDC.RB.x, rectNDC.RB.y, 0.0f };

	list->at(0).color.w = alphaVal;
	list->at(1).color.w = alphaVal;
	list->at(2).color.w = alphaVal;
	list->at(3).color.w = alphaVal;

	if (!SpriteList.empty())
	{
		// Set Sprite Region
		float textureWidth = pShader->getTextureWidth();
		float textureHeight = pShader->getTextureHeight();

		Rect_<float> rect = SpriteList[SpriteNum];
		list->at(0).texture = { rect.left() / textureWidth, rect.top() / textureHeight }; // p1-LT
		list->at(1).texture = { rect.right() / textureWidth, rect.top() / textureHeight }; // p2-RT
		list->at(2).texture = { rect.left() / textureWidth, rect.bottom() / textureHeight }; // p3-LB
		list->at(3).texture = { rect.right() / textureWidth, rect.bottom() / textureHeight }; // p4-RB

		if (filpSpriteHorizontal)
		{
			Vector2f LT = list->at(0).texture;
			Vector2f RT = list->at(1).texture;
			Vector2f LB = list->at(2).texture;
			Vector2f RB = list->at(3).texture;
			list->at(0).texture = RT; //{ 0.0f, 0.0f }; // LT
			list->at(1).texture = LT; //{ 1.0f, 0.0f }; // RT
			list->at(2).texture = RB; //{ 0.0f, 1.0f }; // LB
			list->at(3).texture = LB; //{ 1.0f, 1.0f }; // RB
		}

		if (filpSpriteVertical)
		{
			Vector2f LT = list->at(0).texture;
			Vector2f RT = list->at(1).texture;
			Vector2f LB = list->at(2).texture;
			Vector2f RB = list->at(3).texture;
			list->at(0).texture = LB;
			list->at(1).texture = RB;
			list->at(2).texture = LT;
			list->at(3).texture = RT;
		}
	}

	Matrix4x4 s = Make3DMatrix_Scale(2.0f, 2.0f, 2.0f);
	//Matrix r = Make3DMatrix_RotationY(DegreeToRadian(testVal));
	//Matrix r2 = Make3DMatrix_RotationX(DegreeToRadian(testVal));
	float rotVal = PI * cos(DegreeToRadian(testVal));
	Matrix4x4 rx = Make3DMatrix_RotationX(rotVal);
	Matrix4x4 ry = Make3DMatrix_RotationY(rotVal);
	Matrix4x4 rz = Make3DMatrix_RotationZ(rotVal);
	Matrix4x4 t = Make3DMatrix_Translation(0.0f, 0.0f, 0.0f);
	Matrix4x4 srt = s * rx * ry * rz * t;
	testVal += 0.02f;

	for (int i = 0; i < list->size(); i++)
	{
		Vector4f temp = Vector4f(list->at(i).pos.x, list->at(i).pos.y, list->at(i).pos.z, 1.0f);
		temp = temp * srt;
		list->at(i).pos = Vector3f(temp.x, temp.y, 0.0f);
	}
}

void NewObject::updateShaderCamera()
{
	Rect_<float> rectOrthogonal = ScreenToOrthogonal(shape);
	Rect_<float> rectNDC;
	if (renderCamera != nullptr)
	{
		rectNDC = OrthogonalToNDC_Camera(rectOrthogonal);
	}
	else
	{
		rectNDC = OrthogonalToNDC(rectOrthogonal);
	}

	// Vectex List
	std::vector<Vertex>* list = pShader->getVertexList();
	list->at(0).pos = { rectNDC.LT.x, rectNDC.LT.y, 0.0f };
	list->at(1).pos = { rectNDC.RB.x, rectNDC.LT.y, 0.0f };
	list->at(2).pos = { rectNDC.LT.x, rectNDC.RB.y, 0.0f };
	list->at(3).pos = { rectNDC.RB.x, rectNDC.RB.y, 0.0f };

	float cosAngleVal = cos(DegreeToRadian(angle));
	float sinAngleVal = sin(DegreeToRadian(angle));

	Vector3f center;
	center.x = (list->at(0).pos.x + list->at(1).pos.x) / 2.0f;
	center.y = (list->at(0).pos.y + list->at(2).pos.y) / 2.0f;

	Vector3f centerMoved;
	centerMoved = list->at(0).pos - center;
	Vector3f rstRotation;
	rstRotation.x = centerMoved.x * cosAngleVal - centerMoved.y * sinAngleVal;
	rstRotation.y = centerMoved.x * sinAngleVal + centerMoved.y * cosAngleVal;
	list->at(0).pos = rstRotation + center;

	centerMoved = list->at(1).pos - center;
	rstRotation.x = centerMoved.x * cosAngleVal - centerMoved.y * sinAngleVal;
	rstRotation.y = centerMoved.x * sinAngleVal + centerMoved.y * cosAngleVal;
	list->at(1).pos = rstRotation + center;

	centerMoved = list->at(2).pos - center;
	rstRotation.x = centerMoved.x * cosAngleVal - centerMoved.y * sinAngleVal;
	rstRotation.y = centerMoved.x * sinAngleVal + centerMoved.y * cosAngleVal;
	list->at(2).pos = rstRotation + center;

	centerMoved = list->at(3).pos - center;
	rstRotation.x = centerMoved.x * cosAngleVal - centerMoved.y * sinAngleVal;
	rstRotation.y = centerMoved.x * sinAngleVal + centerMoved.y * cosAngleVal;
	list->at(3).pos = rstRotation + center;



	list->at(0).color = { 1.0f, 1.0f, 1.0f, alphaVal };
	list->at(1).color = { 1.0f, 1.0f, 1.0f, alphaVal };
	list->at(2).color = { 1.0f, 1.0f, 1.0f, alphaVal };
	list->at(3).color = { 1.0f, 1.0f, 1.0f, alphaVal };

	if (!SpriteList.empty())
	{
		// Set Sprite Region
		float textureWidth = pShader->getTextureWidth();
		float textureHeight = pShader->getTextureHeight();

		Rect_<float> rect = SpriteList[SpriteNum];
		list->at(0).texture = { rect.left() / textureWidth, rect.top() / textureHeight }; // p1-LT
		list->at(1).texture = { rect.right() / textureWidth, rect.top() / textureHeight }; // p2-RT
		list->at(2).texture = { rect.left() / textureWidth, rect.bottom() / textureHeight }; // p3-LB
		list->at(3).texture = { rect.right() / textureWidth, rect.bottom() / textureHeight }; // p4-RB

		if (filpSpriteHorizontal)
		{
			Vector2f LT = list->at(0).texture;
			Vector2f RT = list->at(1).texture;
			Vector2f LB = list->at(2).texture;
			Vector2f RB = list->at(3).texture;
			list->at(0).texture = RT; //{ 0.0f, 0.0f }; // LT
			list->at(1).texture = LT; //{ 1.0f, 0.0f }; // RT
			list->at(2).texture = RB; //{ 0.0f, 1.0f }; // LB
			list->at(3).texture = LB; //{ 1.0f, 1.0f }; // RB
		}

		if (filpSpriteVertical)
		{
			Vector2f LT = list->at(0).texture;
			Vector2f RT = list->at(1).texture;
			Vector2f LB = list->at(2).texture;
			Vector2f RB = list->at(3).texture;
			list->at(0).texture = LB;
			list->at(1).texture = RB;
			list->at(2).texture = LT;
			list->at(3).texture = RT;
		}
	}
}

bool BoxObject::init()
{
	
	return false;
}

void BoxObject::updateShader()
{
}

void BoxObject::updateShaderCamera()
{
}
