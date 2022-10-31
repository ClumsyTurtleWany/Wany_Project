#pragma once
#include "Define.hpp"
//#include "fbxsdk.h" // 헤더 안에 하위 헤더들을 불러오지 못함.
#include <fbxsdk.h>
#include "Object.hpp"
//#pragma comment(lib, "libfbxsdk.lib")
#pragma comment(lib, "libfbxsdk-md.lib") // 다중 스레드 디버그 dll (md), 다중 스레드 (mt)
#pragma comment(lib, "libxml2-md.lib") // libfbxsdk-md 에 필요한 lib
#pragma comment(lib, "zlib-md.lib") // libfbxsdk-md 에 필요한 lib

#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#pragma warning(disable : 26812)

class FBXLoader
{
private:
	FbxManager*		m_pManager = nullptr;
	FbxImporter*	m_pImporter = nullptr;
	FbxScene*		m_pScene = nullptr;
	FbxNode*		m_pRoot = nullptr; // Tree 구조로 되어있음.

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