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
	std::vector<Vertex> VertexList;
	VertexList.resize(24);

	VertexList[0] = Vertex(Vector3f(-1.0f, 1.0f, -1.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[1] = Vertex(Vector3f(1.0f, 1.0f, -1.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f), Vector2f(1.0f, 0.0f));
	VertexList[2] = Vertex(Vector3f(1.0f, -1.0f, -1.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f), Vector2f(1.0f, 1.0f));
	VertexList[3] = Vertex(Vector3f(-1.0f, -1.0f, -1.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f), Vector2f(0.0f, 1.0f));
	// µÞ¸é
	VertexList[4] = Vertex(Vector3f(1.0f, 1.0f, 1.0f), Vector4f(0.0f, 0.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[5] = Vertex(Vector3f(-1.0f, 1.0f, 1.0f), Vector4f(0.0f, 1.0f, 0.0f, 1.0f), Vector2f(1.0f, 0.0f));
	VertexList[6] = Vertex(Vector3f(-1.0f, -1.0f, 1.0f), Vector4f(0.0f, 1.0f, 0.0f, 1.0f), Vector2f(1.0f, 1.0f));
	VertexList[7] = Vertex(Vector3f(1.0f, -1.0f, 1.0f), Vector4f(0.0f, 1.0f, 0.0f, 1.0f), Vector2f(0.0f, 1.0f));

	// ¿À¸¥ÂÊ
	VertexList[8] = Vertex(Vector3f(1.0f, 1.0f, -1.0f), Vector4f(0.0f, 0.0f, 1.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[9] = Vertex(Vector3f(1.0f, 1.0f, 1.0f), Vector4f(0.0f, 0.0f, 1.0f, 1.0f), Vector2f(1.0f, 0.0f));
	VertexList[10] = Vertex(Vector3f(1.0f, -1.0f, 1.0f), Vector4f(0.0f, 0.0f, 1.0f, 1.0f), Vector2f(1.0f, 1.0f));
	VertexList[11] = Vertex(Vector3f(1.0f, -1.0f, -1.0f), Vector4f(0.0f, 0.0f, 1.0f, 1.0f), Vector2f(0.0f, 1.0f));

	// ¿ÞÂÊ
	VertexList[12] = Vertex(Vector3f(-1.0f, 1.0f, 1.0f), Vector4f(1.0f, 1.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[13] = Vertex(Vector3f(-1.0f, 1.0f, -1.0f), Vector4f(1.0f, 1.0f, 0.0f, 1.0f), Vector2f(1.0f, 0.0f));
	VertexList[14] = Vertex(Vector3f(-1.0f, -1.0f, -1.0f), Vector4f(1.0f, 1.0f, 0.0f, 1.0f), Vector2f(1.0f, 1.0f));
	VertexList[15] = Vertex(Vector3f(-1.0f, -1.0f, 1.0f), Vector4f(1.0f, 1.0f, 0.0f, 1.0f), Vector2f(0.0f, 1.0f));

	// À­¸é
	VertexList[16] = Vertex(Vector3f(-1.0f, 1.0f, 1.0f), Vector4f(1.0f, 0.5f, 1.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[17] = Vertex(Vector3f(1.0f, 1.0f, 1.0f), Vector4f(1.0f, 0.5f, 1.0f, 1.0f), Vector2f(1.0f, 0.0f));
	VertexList[18] = Vertex(Vector3f(1.0f, 1.0f, -1.0f), Vector4f(1.0f, 0.5f, 1.0f, 1.0f), Vector2f(1.0f, 1.0f));
	VertexList[19] = Vertex(Vector3f(-1.0f, 1.0f, -1.0f), Vector4f(1.0f, 0.5f, 1.0f, 1.0f), Vector2f(0.0f, 1.0f));

	// ¾Æ·§¸é
	VertexList[20] = Vertex(Vector3f(-1.0f, -1.0f, -1.0f), Vector4f(0.0f, 1.0f, 1.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[21] = Vertex(Vector3f(1.0f, -1.0f, -1.0f), Vector4f(0.0f, 1.0f, 1.0f, 1.0f), Vector2f(1.0f, 0.0f));
	VertexList[22] = Vertex(Vector3f(1.0f, -1.0f, 1.0f), Vector4f(0.0f, 1.0f, 1.0f, 1.0f), Vector2f(1.0f, 1.0f));
	VertexList[23] = Vertex(Vector3f(-1.0f, -1.0f, 1.0f), Vector4f(0.0f, 1.0f, 1.0f, 1.0f), Vector2f(0.0f, 1.0f));

	pShader->updateVertexList(&VertexList);


	std::vector<DWORD> IndexList;
	IndexList.resize(36);
	int iIndex = 0;
	IndexList[iIndex++] = 0;	IndexList[iIndex++] = 1;	IndexList[iIndex++] = 2; 	IndexList[iIndex++] = 0;	IndexList[iIndex++] = 2; 	IndexList[iIndex++] = 3;
	IndexList[iIndex++] = 4;	IndexList[iIndex++] = 5;	IndexList[iIndex++] = 6; 	IndexList[iIndex++] = 4;	IndexList[iIndex++] = 6; 	IndexList[iIndex++] = 7;
	IndexList[iIndex++] = 8;	IndexList[iIndex++] = 9;	IndexList[iIndex++] = 10;	IndexList[iIndex++] = 8;	IndexList[iIndex++] = 10;	IndexList[iIndex++] = 11;
	IndexList[iIndex++] = 12;	IndexList[iIndex++] = 13;	IndexList[iIndex++] = 14;	IndexList[iIndex++] = 12;	IndexList[iIndex++] = 14;	IndexList[iIndex++] = 15;
	IndexList[iIndex++] = 16;	IndexList[iIndex++] = 17;	IndexList[iIndex++] = 18;	IndexList[iIndex++] = 16;	IndexList[iIndex++] = 18;	IndexList[iIndex++] = 19;
	IndexList[iIndex++] = 20;	IndexList[iIndex++] = 21;	IndexList[iIndex++] = 22;	IndexList[iIndex++] = 20;	IndexList[iIndex++] = 22;	IndexList[iIndex++] = 23;

	pShader->updateIndexList(&IndexList);

	return true;
}

void BoxObject::updateShader()
{
}

void BoxObject::updateShaderCamera()
{
}
