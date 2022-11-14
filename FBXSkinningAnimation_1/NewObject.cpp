#include "NewObject.hpp"

bool Plane3D::initialize()
{
	axis.createShader(ShaderType::Axis3D);
	axis.setAxisSize(2.0f, 2.0f, 2.0f);
	axis.initialize();

	pShader->setCullMode(CullMode::None);

	initializeVertexList();
	initializeIndexList();
	return true;
}

bool Plane3D::initializeVertexList()
{
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

	return pShader->updateVertexList(&VertexList);
}

bool Plane3D::initializeIndexList()
{
	IndexList.assign(6, 0);
	IndexList[0] = 0;
	IndexList[1] = 1;
	IndexList[2] = 2;
	IndexList[3] = 2;
	IndexList[4] = 1;
	IndexList[5] = 3;
	return pShader->updateIndexList(&IndexList);
}

bool Plane3D::render()
{
	axis.setMatrix(&data.matWorld, &data.matView, &data.matProj);
	axis.render();
	pShader->render();
	return true;
}

bool Plane3D::frame(float _dt)
{
	curPos = Vector3f(0.0f, 0.0f, 0.0f) * data.matWorld;
	return true;
}

bool Cube3D::initialize()
{
	axis.createShader(ShaderType::Axis3D);
	axis.setAxisSize(2.0f, 2.0f, 2.0f);
	axis.initialize();

	initializeVertexList();
	initializeIndexList();
	return true;
}

bool Cube3D::initializeVertexList()
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

	return pShader->updateVertexList(&VertexList);
}

bool Cube3D::initializeIndexList()
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

bool Cube3D::render()
{
	axis.setMatrix(&data.matWorld, &data.matView, &data.matProj);
	axis.render();
	pShader->render();
	return true;
}

bool Cube3D::frame(float _dt)
{
	curPos = Vector3f(0.0f, 0.0f, 0.0f) * data.matWorld;
	return true;
}

bool Cube3D::rotationYawPitchRoll(float _yaw, float _pitch, float _roll)
{
	Vector3f translate = Vector3f(data.matWorld._41, data.matWorld._42, data.matWorld._43);
	DirectX::XMMATRIX matWorld = DirectX::XMMatrixRotationRollPitchYaw(_pitch, _yaw, _roll);
	data.matWorld = *((Matrix4x4*)&matWorld);
	data.matWorld._41 += translate.x;
	data.matWorld._42 += translate.y;
	data.matWorld._43 += translate.z;
	return true;
}

bool Map3D::build(int _width, int _height)
{
	// width와 height는 2^n + 1 으로 생성하는게 좋다. 그래야 셀이 잘리지 않는다.
	//std::vector<Vertex> VertexList;
	int vertexCount = _width * _height;
	int cellCount = (_width - 1) * (_height - 1); // 셀
	faceCount = cellCount * 2;
	VertexList.resize(vertexCount);

	int width_half = _width / 2;
	int height_half = _height / 2;
	float cellDistance = 1.0f;
	for (int row = 0; row < _height; row++)
	{
		for (int col = 0; col < _width; col++)
		{
			int idx = row * _width + col;
			VertexList[idx].color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);

			VertexList[idx].pos = Vector3f(static_cast<float>(col - width_half) * cellDistance,
				/*cosf(DegreeToRadian(col)) * 20.0f + sinf(DegreeToRadian(row)) * 20.0f*/0.0f,
				static_cast<float>(height_half - row) * cellDistance);

			VertexList[idx].texture =
				Vector2f((static_cast<float>(col) / static_cast<float>(_width - 1)) * 10.0f,
					(static_cast<float>(row) / static_cast<float>(_height - 1)) * 10.0f);

			//VertexList[idx].normal = Vector3f(0.0f, 1.0f, 0.0f);

		}
	}

	pShader->updateVertexList(&VertexList);

	//std::vector<DWORD> IndexList;
	int indexCount = faceCount * 3;
	IndexList.resize(indexCount);
	size_t idx = 0;
	for (int row = 0; row < _height - 1; row++)
	{
		for (int col = 0; col < _width - 1; col++)
		{
			//int idx = row * (_width - 1) + col;
			IndexList[idx + 0] = row * _width + col;
			IndexList[idx + 1] = row * _width + col + 1;
			IndexList[idx + 2] = (row + 1) * _width + col;

			IndexList[idx + 3] = (row + 1) * _width + col;
			IndexList[idx + 4] = row * _width + col + 1;
			IndexList[idx + 5] = (row + 1) * _width + col + 1;

			idx += 6;
		}
	}

	pShader->updateIndexList(&IndexList);

	GenerateNormal();

	axis.createShader(ShaderType::Axis3D);
	axis.setAxisSize(_width * 2.0f, 100.0f, _height * 2.0f);
	axis.initialize();

	return true;
}

bool Map3D::LoadHeightMap(std::wstring _filename)
{
	// Texture에 접근하기 위해선 CPU에 접근 해야함. 

	return false;
}

bool Map3D::GenerateNormal()
{
	if (IndexList.empty() || VertexList.empty())
	{
		return false;
	}

	std::vector<Vector3f> FaceNormal;
	FaceNormal.resize(faceCount);
	// Index 순회하며 각 Face의 Normal값 생성.
	for (size_t idx = 0; idx < IndexList.size(); idx += 3)
	{
		DWORD i0 = IndexList[idx + 0];
		DWORD i1 = IndexList[idx + 1];
		DWORD i2 = IndexList[idx + 2];
		FaceNormal[idx / 3] = ComputeFaceNormal(i0, i1, i2);
	}

	struct VertexFaceInfo
	{
		std::vector<UINT> faceIndexList;
		//std::vector<UINT> edgeList; // 원래는 엣지도 다 가지고 있어야 함.
		Vector3f normal;
	};
	std::vector<VertexFaceInfo> VertexFaceInfoList; // Face Look Up Table
	VertexFaceInfoList.resize(VertexList.size());
	for (UINT FaceIdx = 0; FaceIdx < faceCount; FaceIdx++)
	{
		for (UINT idx = 0; idx < 3; idx++)
		{
			UINT VertexID = IndexList[idx + 0];
			VertexFaceInfoList[VertexID].faceIndexList.push_back(FaceIdx);
		}
	}

	for (UINT VertexIdx = 0; VertexIdx < VertexList.size(); VertexIdx++)
	{
		for (UINT idx = 0; idx < VertexFaceInfoList[VertexIdx].faceIndexList.size(); idx++)
		{
			UINT FaceID = VertexFaceInfoList[VertexIdx].faceIndexList[idx];
			VertexFaceInfoList[VertexIdx].normal += FaceNormal[FaceID];
		}
		VertexList[VertexIdx].normal = VertexFaceInfoList[VertexIdx].normal.normalized();
	}

	return true;
}

Vector3f Map3D::ComputeFaceNormal(DWORD _i0, DWORD _i1, DWORD _i2)
{
	Vector3f normal;
	Vector3f v0 = VertexList[_i1].pos - VertexList[_i0].pos;
	Vector3f v1 = VertexList[_i2].pos - VertexList[_i0].pos;
	normal = v0.cross(v1);
	return normal;
}

bool Map3D::render()
{
	axis.setMatrix(&data.matWorld, &data.matView, &data.matProj);
	axis.render();
	pShader->render();
	return true;
}

bool Map3D::frame(float _dt)
{
	curPos = Vector3f(0.0f, 0.0f, 0.0f) * data.matWorld;
	return true;
}

bool Axis3D::initialize()
{
	pShader->setTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	initializeVertexList();
	initializeIndexList();
	return true;
}

void Axis3D::setAxisSize(float _x, float _y, float _z)
{
	AxisSize.x = _x;
	AxisSize.y = _y;
	AxisSize.z = _z;
}

bool Axis3D::initializeVertexList()
{
	VertexList.resize(6);
	// Axis X
	VertexList[0] = Vertex(Vector3f(0.0f, 0.0f, 0.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f), Vector2f(0.0f, 1.0f));
	VertexList[1] = Vertex(Vector3f(AxisSize.x, 0.0f, 0.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f), Vector2f(0.0f, 1.0f));

	// Axis Y
	VertexList[2] = Vertex(Vector3f(0.0f, 0.0f, 0.0f), Vector4f(0.0f, 1.0f, 0.0f, 1.0f), Vector2f(0.0f, 1.0f));
	VertexList[3] = Vertex(Vector3f(0.0f, AxisSize.y, 0.0f), Vector4f(0.0f, 1.0f, 0.0f, 1.0f), Vector2f(0.0f, 1.0f));

	// Axis Z
	VertexList[4] = Vertex(Vector3f(0.0f, 0.0f, 0.0f), Vector4f(0.0f, 0.0f, 1.0f, 1.0f), Vector2f(0.0f, 0.0f));
	VertexList[5] = Vertex(Vector3f(0.0f, 0.0f, AxisSize.z), Vector4f(0.0f, 0.0f, 1.0f, 1.0f), Vector2f(0.0f, 1.0f));
	return pShader->updateVertexList(&VertexList);
}

bool Axis3D::initializeIndexList()
{
	IndexList.resize(6);
	IndexList[0] = 0;
	IndexList[1] = 1;
	IndexList[2] = 2;
	IndexList[3] = 3;
	IndexList[4] = 4;
	IndexList[5] = 5;
	return pShader->updateIndexList(&IndexList);
}
