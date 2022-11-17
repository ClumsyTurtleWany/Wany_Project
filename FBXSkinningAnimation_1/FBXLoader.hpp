#pragma once
#include "Define.hpp"
//#include "fbxsdk.h" // 헤더 안에 하위 헤더들을 불러오지 못함.
#include <fbxsdk.h>
//#pragma comment(lib, "libfbxsdk.lib")
#pragma comment(lib, "libfbxsdk-md.lib") // 다중 스레드 디버그 dll (md), 다중 스레드 (mt)
#pragma comment(lib, "libxml2-md.lib") // libfbxsdk-md 에 필요한 lib
#pragma comment(lib, "zlib-md.lib") // libfbxsdk-md 에 필요한 lib

#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#pragma warning(disable : 26812)

#include "FBXObject.hpp"
#include "DXTextureManager.hpp"
#include "DXMath.hpp"


class FBXLoader : public Singleton<FBXLoader>
{
private:
	friend class Singleton<FBXLoader>;

	FbxManager*		m_pManager = nullptr;
	FbxImporter*	m_pImporter = nullptr;
	
	std::wstring	m_wstrResourceDir = L"";

	std::map<std::wstring, std::unique_ptr<FBXObject>> m_ObjectMap;

public:
	virtual bool initialize();
	virtual bool frame();
	virtual bool render();
	virtual bool release();

private:
	// Parser
	bool ParseScene(FbxScene* _scene, FBXFileData* _dst);
	bool ParseNode(FbxNode* _node, FBXFileData* _dst);
	bool PreProcess(FBXFileData* _dst);
	bool ParseMesh(FbxMesh* _mesh, FBXFileData* _dst, FBXNodeData* _dstData);
	bool ParseMeshLayer(FbxMesh* _mesh, MeshData* _dstData);
	bool ParseMeshSkinning(FbxMesh* _mesh, FBXFileData* _dst, FBXNodeData* _dstData);
	bool ParseDummy(FbxNull* _dummy, FBXFileData* _dst);
	bool ParseSkeleton(FbxSkeleton* _skeleton, FBXFileData* _dst);
	
	
	// Read Data
	bool ReadTextureCoord(FbxLayerElementUV* _uv, int _vertexIdx, int _uvIdx, FbxVector2& _dst);
	bool ReadColorCoord(FbxLayerElementVertexColor* _color, int _vertexIdx, int _colorIdx, FbxColor& _dst);
	bool ReadNormal(FbxLayerElementNormal* _normal, int _vertexIdx, int _normalIdx, FbxVector4& _dst);

	int getSubMaterialIndex(FbxLayerElementMaterial* _material, int _polyIdx);

	DXTexture* FindTexture(FbxSurfaceMaterial* _surface, const char* _name, std::wstring* _rst = nullptr);
	std::wstring getTextureFileName(FbxSurfaceMaterial* _surface, const char* _name);

	// Matrix
	FbxAMatrix getGeometryMatrix(FbxNode* _node);
	FbxAMatrix getNormalMatrix(const FbxAMatrix& _src);
	FbxAMatrix getWorldMatrix(FbxNode* _node);

public:
	bool LoadDir(std::wstring _path);
	bool Load(std::wstring _path, FBXObject* _dst);

public:
	FBXObject* getObject(std::wstring _key);

public:
	void setResourceDirectory(std::wstring _dir);

public:
	Matrix4x4 toMatrix4x4(const FbxAMatrix& _src);
	Matrix4x4 ConvertToDxMatrix(const FbxAMatrix& _src);

public:
	bool GenerateAnimationTrack(FBXFileData* _data);
	bool GenerateObjectFromFileData(FBXObject* _dst);
};