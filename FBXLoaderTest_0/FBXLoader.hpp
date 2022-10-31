#pragma once
#include "Define.hpp"
//#include "fbxsdk.h" // ��� �ȿ� ���� ������� �ҷ����� ����.
#include <fbxsdk.h>
#include "Object.hpp"
//#pragma comment(lib, "libfbxsdk.lib")
#pragma comment(lib, "libfbxsdk-md.lib") // ���� ������ ����� dll (md), ���� ������ (mt)
#pragma comment(lib, "libxml2-md.lib") // libfbxsdk-md �� �ʿ��� lib
#pragma comment(lib, "zlib-md.lib") // libfbxsdk-md �� �ʿ��� lib

#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#pragma warning(disable : 26812)

class FBXLoader
{
private:
	FbxManager*		m_pManager = nullptr;
	FbxImporter*	m_pImporter = nullptr;
	FbxScene*		m_pScene = nullptr;
	FbxNode*		m_pRoot = nullptr; // Tree ������ �Ǿ�����.

	std::vector<FbxMesh*> m_MeshList;


	std::vector<object3D<float>*> m_objList;

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();

public:
	bool Load(const char* _filename, std::vector<std::vector<Vertex>>& _dst);
	bool PreProcess(FbxNode* _node);
	bool ParseMesh(FbxMesh* _mesh, std::vector<Vertex>& _dst);
	bool ReadTextureCoord(FbxLayerElementUV* _uv, int _vertexIdx, int _uvIdx, FbxVector2& _dst);
	bool ReadColorCoord(FbxLayerElementVertexColor* _uv, int _vertexIdx, int _colorIdx, FbxVector4& _dst);
};