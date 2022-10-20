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

	//Matrix4x4 s = Make3DMatrix_Scale(2.0f, 2.0f, 2.0f);
	////Matrix r = Make3DMatrix_RotationY(DegreeToRadian(testVal));
	////Matrix r2 = Make3DMatrix_RotationX(DegreeToRadian(testVal));
	//float rotVal = PI * cos(DegreeToRadian(testVal));
	//Matrix4x4 rx = Make3DMatrix_RotationX(rotVal);
	//Matrix4x4 ry = Make3DMatrix_RotationY(rotVal);
	//Matrix4x4 rz = Make3DMatrix_RotationZ(rotVal);
	//Matrix4x4 t = Make3DMatrix_Translation(0.0f, 0.0f, 0.0f);
	//Matrix4x4 srt = s * rx * ry * rz * t;
	//testVal += 0.02f;

	//for (int i = 0; i < list->size(); i++)
	//{
	//	Vector4f temp = Vector4f(list->at(i).pos.x, list->at(i).pos.y, list->at(i).pos.z, 1.0f);
	//	temp = temp * srt;
	//	list->at(i).pos = Vector3f(temp.x, temp.y, 0.0f);
	//}
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

bool NewObject::setMatrix(Matrix4x4 _world, Matrix4x4 _view, Matrix4x4 _proj)
{
	data.matWorld = _world; // .Transpose();
	data.matView = _view; // .Transpose();
	data.matProj = _proj; // .Transpose();
	pShader->updateConstantData(&data);
	return true;
}

bool NewObject::render()
{
	std::vector<Vertex> VertexList;
	VertexList.assign(4, Vertex());
	VertexList[0].pos = { -1.0f, +1.0f, 0.0f }; // p1-LT
	VertexList[1].pos = { +1.0f, +1.0f, 0.0f }; // p2-RT
	VertexList[2].pos = { -1.0f, -1.0f, 0.0f }; // p3-LB
	VertexList[3].pos = { +1.0f, -1.0f, 0.0f }; // p4-LB
	
	VertexList[0].color = { 1.0f, 1.0f, 1.0f, 1.0f }; // p1-LT
	VertexList[1].color = { 1.0f, 1.0f, 1.0f, 1.0f }; // p2-RT
	VertexList[2].color = { 1.0f, 1.0f, 1.0f, 1.0f }; // p3-LB
	VertexList[3].color = { 1.0f, 1.0f, 1.0f, 1.0f }; // p4-LB
	
	VertexList[0].texture = { 0.0f, 0.0f }; // p1-LT
	VertexList[1].texture = { 1.0f, 0.0f }; // p2-RT
	VertexList[2].texture = { 0.0f, 1.0f }; // p3-LB
	VertexList[3].texture = { 1.0f, 1.0f }; // p4-LB

	std::vector<Vertex>* list;
	list = pShader->getVertexList();

	pShader->updateVertexList(&VertexList);
	
	bool bTest = false;
	if (bTest)
	{
		data.matWorld._41 = 1.0f;

		for (size_t idx = 0; idx < list->size(); idx++)
		{
			Vector3f temp = VertexList[idx].pos;
			Vector4f local = (Vector4f(temp.x, temp.y, temp.z, 1.0f));
			Vector4f world = local * data.matWorld;
			Vector4f view = world * data.matView;
			Vector4f proj = view * data.matProj;
			float w = proj.x * data.matProj._14 + proj.y * data.matProj._24 + proj.z * data.matProj._34 + 1.0f * data.matProj._44;
			proj.x /= w;
			proj.y /= w;
			proj.z /= w;
			list->at(idx).pos = Vector3f(proj.x, proj.y, proj.z);
		}

		Matrix4x4 identity;
		identity.Identity();
		data.matWorld = identity;
		data.matView = identity;
		data.matProj = identity;

		//data.matWorld = identity * (0.75f + cosf(testTime) / 4.0f);
		//data.matWorld._44 = 1.0f;
		//data.matWorld._41 = -1.0f;
	}
	
	//data.matWorld = identity * (0.75f + cosf(testTime) / 4.0f);
	//data.matWorld._44 = 1.0f;
	data.matWorld._41 = 1.0f;
	//data.matWorld._42 = 0.0f;
	//data.time1 = data.matProj._14;
	//data.time2 = data.matProj._24;
	//data.time3 = data.matProj._34;
	//data.time4 = data.matProj._44;
	pShader->updateConstantData(&data);
	pShader->render();
	return true;
}

bool BoxObject::initVertex()
{
	VertexList.resize(24);

	VertexList[0] = Vertex(Vector3f(-1.0f, 1.0f, -1.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[1] = Vertex(Vector3f(1.0f, 1.0f, -1.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f), Vector2f(1.0f, 0.0f));
	VertexList[2] = Vertex(Vector3f(1.0f, -1.0f, -1.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f), Vector2f(1.0f, 1.0f));
	VertexList[3] = Vertex(Vector3f(-1.0f, -1.0f, -1.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f), Vector2f(0.0f, 1.0f));
	// 뒷면
	VertexList[4] = Vertex(Vector3f(1.0f, 1.0f, 1.0f), Vector4f(0.0f, 0.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[5] = Vertex(Vector3f(-1.0f, 1.0f, 1.0f), Vector4f(0.0f, 1.0f, 0.0f, 1.0f), Vector2f(1.0f, 0.0f));
	VertexList[6] = Vertex(Vector3f(-1.0f, -1.0f, 1.0f), Vector4f(0.0f, 1.0f, 0.0f, 1.0f), Vector2f(1.0f, 1.0f));
	VertexList[7] = Vertex(Vector3f(1.0f, -1.0f, 1.0f), Vector4f(0.0f, 1.0f, 0.0f, 1.0f), Vector2f(0.0f, 1.0f));

	// 오른쪽
	VertexList[8] = Vertex(Vector3f(1.0f, 1.0f, -1.0f), Vector4f(0.0f, 0.0f, 1.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[9] = Vertex(Vector3f(1.0f, 1.0f, 1.0f), Vector4f(0.0f, 0.0f, 1.0f, 1.0f), Vector2f(1.0f, 0.0f));
	VertexList[10] = Vertex(Vector3f(1.0f, -1.0f, 1.0f), Vector4f(0.0f, 0.0f, 1.0f, 1.0f), Vector2f(1.0f, 1.0f));
	VertexList[11] = Vertex(Vector3f(1.0f, -1.0f, -1.0f), Vector4f(0.0f, 0.0f, 1.0f, 1.0f), Vector2f(0.0f, 1.0f));

	// 왼쪽
	VertexList[12] = Vertex(Vector3f(-1.0f, 1.0f, 1.0f), Vector4f(1.0f, 1.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[13] = Vertex(Vector3f(-1.0f, 1.0f, -1.0f), Vector4f(1.0f, 1.0f, 0.0f, 1.0f), Vector2f(1.0f, 0.0f));
	VertexList[14] = Vertex(Vector3f(-1.0f, -1.0f, -1.0f), Vector4f(1.0f, 1.0f, 0.0f, 1.0f), Vector2f(1.0f, 1.0f));
	VertexList[15] = Vertex(Vector3f(-1.0f, -1.0f, 1.0f), Vector4f(1.0f, 1.0f, 0.0f, 1.0f), Vector2f(0.0f, 1.0f));

	// 윗면
	VertexList[16] = Vertex(Vector3f(-1.0f, 1.0f, 1.0f), Vector4f(1.0f, 0.5f, 1.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[17] = Vertex(Vector3f(1.0f, 1.0f, 1.0f), Vector4f(1.0f, 0.5f, 1.0f, 1.0f), Vector2f(1.0f, 0.0f));
	VertexList[18] = Vertex(Vector3f(1.0f, 1.0f, -1.0f), Vector4f(1.0f, 0.5f, 1.0f, 1.0f), Vector2f(1.0f, 1.0f));
	VertexList[19] = Vertex(Vector3f(-1.0f, 1.0f, -1.0f), Vector4f(1.0f, 0.5f, 1.0f, 1.0f), Vector2f(0.0f, 1.0f));

	// 아랫면
	VertexList[20] = Vertex(Vector3f(-1.0f, -1.0f, -1.0f), Vector4f(0.0f, 1.0f, 1.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[21] = Vertex(Vector3f(1.0f, -1.0f, -1.0f), Vector4f(0.0f, 1.0f, 1.0f, 1.0f), Vector2f(1.0f, 0.0f));
	VertexList[22] = Vertex(Vector3f(1.0f, -1.0f, 1.0f), Vector4f(0.0f, 1.0f, 1.0f, 1.0f), Vector2f(1.0f, 1.0f));
	VertexList[23] = Vertex(Vector3f(-1.0f, -1.0f, 1.0f), Vector4f(0.0f, 1.0f, 1.0f, 1.0f), Vector2f(0.0f, 1.0f));

	if (!pShader->updateVertexList(&VertexList))
	{
		return false;
	}


	std::vector<DWORD> IndexList;
	IndexList.resize(36);
	int iIndex = 0;
	IndexList[iIndex++] = 0;	IndexList[iIndex++] = 1;	IndexList[iIndex++] = 2; 	IndexList[iIndex++] = 0;	IndexList[iIndex++] = 2; 	IndexList[iIndex++] = 3;
	IndexList[iIndex++] = 4;	IndexList[iIndex++] = 5;	IndexList[iIndex++] = 6; 	IndexList[iIndex++] = 4;	IndexList[iIndex++] = 6; 	IndexList[iIndex++] = 7;
	IndexList[iIndex++] = 8;	IndexList[iIndex++] = 9;	IndexList[iIndex++] = 10;	IndexList[iIndex++] = 8;	IndexList[iIndex++] = 10;	IndexList[iIndex++] = 11;
	IndexList[iIndex++] = 12;	IndexList[iIndex++] = 13;	IndexList[iIndex++] = 14;	IndexList[iIndex++] = 12;	IndexList[iIndex++] = 14;	IndexList[iIndex++] = 15;
	IndexList[iIndex++] = 16;	IndexList[iIndex++] = 17;	IndexList[iIndex++] = 18;	IndexList[iIndex++] = 16;	IndexList[iIndex++] = 18;	IndexList[iIndex++] = 19;
	IndexList[iIndex++] = 20;	IndexList[iIndex++] = 21;	IndexList[iIndex++] = 22;	IndexList[iIndex++] = 20;	IndexList[iIndex++] = 22;	IndexList[iIndex++] = 23;

	if (!pShader->updateIndexList(&IndexList))
	{
		return false;
	}

	return true;
}

bool BoxObject::setMatrix(Matrix4x4 _world, Matrix4x4 _view, Matrix4x4 _proj)
{
	//ConstantBufferData data;
	data.matWorld = _world;
	data.matView = _view;
	data.matProj = _proj;
	pShader->updateConstantData(&data);
	return true;
}

void BoxObject::updateShader()
{
	
}

void BoxObject::updateShaderCamera()
{
	
}

bool BoxObject::render()
{
	pShader->updateConstantData(&data);
	pShader->render();

	return true;
}

bool Map::build(int _width, int _height)
{
	// width와 height는 2^n + 1 으로 생성하는게 좋다. 그래야 셀이 잘리지 않는다.
	std::vector<Vertex> VertexList;
	int vertexCount = _width * _height;
	int cellCount = (_width - 1) * (_height * -1); // 셀
	int faceCount = cellCount * 2;
	VertexList.resize(vertexCount);

	int width_half = _width / 2;
	int height_half = _height / 2;
	float cellDistance = 1.0f;
	for (int row = 0; row < _height; row++)
	{
		for (int col = 0; col < _width; col++)
		{
			int idx = row * _width + col;
			//VertexList[idx].pos = Vector3f(static_cast<float>(col), 0.0f, static_cast<float>(_height - row));
			VertexList[idx].color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);
			VertexList[idx].texture = Vector2f(static_cast<float>(col) / static_cast<float>(_width - 1), static_cast<float>(row) / static_cast<float>(_height - 1));
		
			VertexList[idx].pos = Vector3f(static_cast<float>(col - width_half) * cellDistance, 0.0f, static_cast<float>(height_half - row) * cellDistance);
			
			VertexList[idx].texture = Vector2f(static_cast<float>(col) / static_cast<float>(_width - 1), static_cast<float>(row) / static_cast<float>(_height - 1));

		}
	}

	pShader->updateVertexList(&VertexList);

	std::vector<DWORD> IndexList;
	int indexCount = faceCount * 3;
	IndexList.resize(indexCount);
	for (int row = 0; row < _height  - 1; row++)
	{
		for (int col = 0; col < _width - 1; col++)
		{
			int idx = row * (_width - 1) + col;
			IndexList[idx + 0] = row * _width + col;
			IndexList[idx + 1] = row * _width + col + 1;
			IndexList[idx + 2] = (row + 1) * _width + col;

			IndexList[idx + 3] = (row + 1) * _width + col;
			IndexList[idx + 4] = row * _width + col + 1;
			IndexList[idx + 5] = (row + 1) * _width + col + 1;
		}
	}

	pShader->updateIndexList(&IndexList);

	return false;
}
