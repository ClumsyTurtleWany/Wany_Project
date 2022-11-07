#include "FBXObject.hpp"

bool FBXObject::initialize()
{
	axis.createShader(ShaderType::Axis3D);
	axis.setAxisSize(2.0f, 2.0f, 2.0f);
	axis.initialize();

	//initializeVertexList();
	//initializeIndexList();
	return true;
}

bool FBXObject::initializeVertexList()
{
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

	return pShader->updateVertexList(&VertexList);
}

bool FBXObject::initializeIndexList()
{
	IndexList.resize(36);
	int iIndex = 0;
	IndexList[iIndex++] = 0;	IndexList[iIndex++] = 1;	IndexList[iIndex++] = 2; 	IndexList[iIndex++] = 0;	IndexList[iIndex++] = 2; 	IndexList[iIndex++] = 3;
	IndexList[iIndex++] = 4;	IndexList[iIndex++] = 5;	IndexList[iIndex++] = 6; 	IndexList[iIndex++] = 4;	IndexList[iIndex++] = 6; 	IndexList[iIndex++] = 7;
	IndexList[iIndex++] = 8;	IndexList[iIndex++] = 9;	IndexList[iIndex++] = 10;	IndexList[iIndex++] = 8;	IndexList[iIndex++] = 10;	IndexList[iIndex++] = 11;
	IndexList[iIndex++] = 12;	IndexList[iIndex++] = 13;	IndexList[iIndex++] = 14;	IndexList[iIndex++] = 12;	IndexList[iIndex++] = 14;	IndexList[iIndex++] = 15;
	IndexList[iIndex++] = 16;	IndexList[iIndex++] = 17;	IndexList[iIndex++] = 18;	IndexList[iIndex++] = 16;	IndexList[iIndex++] = 18;	IndexList[iIndex++] = 19;
	IndexList[iIndex++] = 20;	IndexList[iIndex++] = 21;	IndexList[iIndex++] = 22;	IndexList[iIndex++] = 20;	IndexList[iIndex++] = 22;	IndexList[iIndex++] = 23;

	return pShader->updateIndexList(&IndexList);
}

bool FBXObject::render()
{
	//axis.setMatrix(&data.matWorld, &data.matView, &data.matProj);
	//axis.render();

	if (pShader != nullptr)
	{
		pShader->render();
	}

	for (auto it : Materials)
	{
		it.render();
	}

	for (auto it : child)
	{
		it->render();
	}

	return true;
}

bool FBXObject::frame(float _dt)
{
	curPos = Vector3f(0.0f, 0.0f, 0.0f) * data.matWorld;
	return true;
}

bool FBXObject::setMatrix(Matrix4x4* _world, Matrix4x4* _view, Matrix4x4* _proj)
{
	bool isChange = false;
	if (_world != nullptr)
	{
		data.matWorld = (*_world);
		isChange = true;
	}

	if (_view != nullptr)
	{
		data.matView = (*_view);
		isChange = true;
	}

	if (_proj != nullptr)
	{
		data.matProj = (*_proj);
		isChange = true;
	}

	if (isChange)
	{
		//pShader->updateConstantData(&data);
		for (auto it : Materials)
		{
			if (it.Shader == nullptr)
			{
				continue;
			}
			it.Shader->updateConstantData(&data);
		}

		Matrix4x4 matWorld = data.matWorld;
		for (auto it : child)
		{
			//if (it->m_wstrNodeType != L"Mesh")
			//{
			//	continue;
			//}
			
			it->setMatrix(&matWorld, &data.matView, &data.matProj);
			//matWorld._41 += 2.0f;
		}

		return true;
	}
	else
	{
		return true;
	}
}

bool FBXObject::rotationYawPitchRoll(float _yaw, float _pitch, float _roll)
{
	Vector3f translate = Vector3f(data.matWorld._41, data.matWorld._42, data.matWorld._43);
	DirectX::XMMATRIX matWorld = DirectX::XMMatrixRotationRollPitchYaw(_pitch, _yaw, _roll);
	data.matWorld = *((Matrix4x4*)&matWorld);
	data.matWorld._41 += translate.x;
	data.matWorld._42 += translate.y;
	data.matWorld._43 += translate.z;
	return true;
}