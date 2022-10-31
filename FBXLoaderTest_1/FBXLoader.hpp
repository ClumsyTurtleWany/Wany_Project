#pragma once
#include "Define.hpp"
//#include "fbxsdk.h" // ��� �ȿ� ���� ������� �ҷ����� ����.
#include <fbxsdk.h>
//#pragma comment(lib, "libfbxsdk.lib")
#pragma comment(lib, "libfbxsdk-md.lib") // ���� ������ ����� dll (md), ���� ������ (mt)
#pragma comment(lib, "libxml2-md.lib") // libfbxsdk-md �� �ʿ��� lib
#pragma comment(lib, "zlib-md.lib") // libfbxsdk-md �� �ʿ��� lib

#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#pragma warning(disable : 26812)

#include "FBXObject.hpp"
#include "DXTextureManager.hpp"

class FBXLoader : public Singleton<FBXLoader>
{
private:
	friend class Singleton<FBXLoader>;

	FbxManager*		m_pManager = nullptr;
	FbxImporter*	m_pImporter = nullptr;
	//FbxScene*		m_pScene = nullptr; // �� ���ϸ��� ���Ӱ� ������ ��� ��.
	//FbxNode*		m_pRoot = nullptr; // Tree ������ �Ǿ�����. �� ���ϸ��� ���Ӱ� ������ ��� ��.
	//std::vector<FbxMesh*> m_MeshList;

	std::map<std::wstring, std::unique_ptr<FBXObject>> m_ObjectMap;

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();

public:
	bool LoadDir(std::wstring _path);
	bool Load(std::wstring _path, FBXObject* _dst);
	//bool Load(const char* _filename, std::vector<std::vector<Vertex>>& _dst);
	//bool PreProcess(FbxNode* _node);
	bool ParseNode(FbxNode* _node, FBXObject* _dst);
	bool ParseMesh(FbxMesh* _mesh, FBXObject* _dst);
	//bool ParseMesh(FbxMesh* _mesh, std::vector<Vertex>& _dst);
	bool ReadTextureCoord(FbxLayerElementUV* _uv, int _vertexIdx, int _uvIdx, FbxVector2& _dst);
	bool ReadColorCoord(FbxLayerElementVertexColor* _color, int _vertexIdx, int _colorIdx, FbxColor& _dst);
	
	int getSubMaterialIndex(FbxLayerElementMaterial* _material, int _polyIdx);

	DXTexture* FindTexture(FbxSurfaceMaterial* _surface, const char* _name);

	FBXObject* getObject(std::wstring _key);
};