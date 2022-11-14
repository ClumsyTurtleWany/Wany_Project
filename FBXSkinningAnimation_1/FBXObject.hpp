#pragma once
#include "Object.hpp"
#include "NewObject.hpp"

//#include "fbxsdk.h" // 헤더 안에 하위 헤더들을 불러오지 못함.
#include <fbxsdk.h>
//#pragma comment(lib, "libfbxsdk.lib")
#pragma comment(lib, "libfbxsdk-md.lib") // 다중 스레드 디버그 dll (md), 다중 스레드 (mt)
#pragma comment(lib, "libxml2-md.lib") // libfbxsdk-md 에 필요한 lib
#pragma comment(lib, "zlib-md.lib") // libfbxsdk-md 에 필요한 lib

#pragma warning(disable : 26451)
#pragma warning(disable : 26495)
#pragma warning(disable : 26812)

#include "DXMath.hpp"
#include <set>

struct FBXAnimationTrack
{
	UINT frame;
	Matrix4x4 matAnimation; // self * parent
	Matrix4x4 matSelfAnimation;  // matAnimation * inv(Parent)
	Vector3f translation;
	Vector4f rotation; // Quaternion
	Vector3f scale;
};

struct FBXAnimationSceneInfo
{
	FbxTime::EMode TimeMode;
	UINT StartFrame;
	UINT EndFrame;
	float TickPerFrame = 160.0f;
	float FrameSpeed = 30.0f;
};

struct SkinWeight
{
	float weight = 0.0f;
	std::string BoneName = "";

	bool operator <(const SkinWeight& _comp) const
	{
		return weight < _comp.weight;
	}

	bool operator >(const SkinWeight& _comp) const
	{
		return weight > _comp.weight;
	}
};

struct SkinningData
{
	// IndexWeightData 에 넘겨주는건 4개니까, Sort 해서 넣어두는게 사용하기에 좋다.
	std::multiset<SkinWeight, std::greater<SkinWeight>> SkinWeightList;

	void insert(float _weight, std::string _boneName)
	{
		SkinWeight data;
		data.weight = _weight;
		data.BoneName = _boneName;
		SkinWeightList.insert(data);
	}

	void insert(SkinWeight _data)
	{
		SkinWeightList.insert(_data);
	}
};

struct Material
{
	DXShader* Shader = nullptr;
	FbxSurfaceMaterial* Surface;

	std::vector<Vertex> VertexList;
	std::vector<DWORD> IndexList;
	std::vector<IndexWeightData> IWList;
	
	std::wstring DiffuseTexture;

	bool isValid()
	{
		if (VertexList.empty())
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void push_back(const Vertex& _vertex, const IndexWeightData& _IW = IndexWeightData())
	{
		VertexList.push_back(_vertex);
		IWList.push_back(_IW);
	}

	void render()
	{
		if (Shader != nullptr)
		{
			Shader->render();
		}
	}

	void create()
	{
		unsigned int ShaderID = DXShaderManager::getInstance()->getShaderCount();
		if (DXShaderManager::getInstance()->Load(ShaderID, ShaderType::Animation3D))
		{
			Shader = DXShaderManager::getInstance()->getShader(ShaderID);
			if (Shader != nullptr)
			{
				for (int cnt = 0; cnt < VertexList.size(); cnt++)
				{
					IndexList.push_back(cnt);
				}

				Shader->updateVertexList(&VertexList);
				Shader->updateIndexList(&IndexList);

				Shader->setCullMode(CullMode::None);

				DXAnimationShader* pAnimationShader = reinterpret_cast<DXAnimationShader*>(Shader);
				pAnimationShader->updateIWList(&IWList);
			}
		}
	}

	bool setTexture(DXTexture* _texture)
	{
		if ((Shader == nullptr) || (_texture == nullptr))
		{
			return false;
		}
		
		Shader->setTexture(_texture);
		return true;
	}
};

struct Layer
{
	FbxLayerElementUV*			ElementUV = nullptr;
	FbxLayerElementVertexColor* ElementColor = nullptr;
	FbxLayerElementMaterial*	ElementMaterialList = nullptr;
	FbxLayerElementNormal*		ElementNormalList = nullptr;

	std::vector<Material> MaterialList;
	void render()
	{
		for (size_t idx = 0; idx < MaterialList.size(); idx++)
		{
			MaterialList[idx].render();
		}
	}
};

struct MeshData
{
	std::vector<Layer> LayerList;
	std::vector<SkinningData> SkinningList;

	int MaterialNum = 0;
	std::vector<std::wstring> MaterialNameList; // Texture File Name

	void render()
	{
		for (size_t idx = 0; idx < LayerList.size(); idx++)
		{
			LayerList[idx].render();
		}
	}
};

struct FBXVertex
{
	FbxVector4 Position;
	FbxVector2 TexUV;
	FbxVector4 Normal;
	FbxVector4 Color;

	Vertex vertex;
	DWORD index;
	IndexWeightData IWData;
	SkinningData skinningData;
};

using FBXAnimationTrackList = std::vector<FBXAnimationTrack>;

struct FBXNodeData
{
	// Node Type
	FbxNodeAttribute::EType AttributeType;

	// Node Name
	std::string				Name;

	FbxNode*				Node = nullptr;
	FbxMesh*				Mesh = nullptr;
	FbxNull*				Dummy = nullptr;
	FbxSkeleton*			Skeleton = nullptr;

	// Local Geometry Matrix
	FbxAMatrix				LocalGeometryMatrix;
	FbxAMatrix				LocalNormalMatrix;

	// Bind Pose Matrix
	Matrix4x4				BindPoseMatrix;

	// Original Animation Track
	FBXAnimationTrackList	AnimationTrack;
	// Interpolation Animation Track
	std::vector<Matrix4x4>	InterpolationFrameMatrix;

	int MaterialNum = 0;
	std::vector<Material> Materials;
};



class FBXFileData
{
public:
	FBXAnimationSceneInfo							AnimationSceneInfo;
	std::map<std::string, FBXAnimationTrackList>	AnimationTrackMap;

	float InterpolationSampling = 100.0f;
	std::map<std::string, std::vector<Matrix4x4>>	InterpolationFrameMatrixList;

	std::map<std::string, Matrix4x4>				BindPoseMap;
	std::map<std::string, FbxAMatrix>				LocalGeometryMatrixMap;
	std::map<std::string, FbxAMatrix>				NormalMatrixMap;

	std::vector<FbxNode*>							NodeList;
	std::vector<std::string>						NodeNameList;
	std::vector<FbxMesh*>							MeshList;
	std::vector<FbxNull*>							DummyList;
	std::vector<FbxSkeleton*>						SkeletonList;

	std::vector<FBXNodeData>						NodeDataList;
	std::vector<MeshData>							MeshDataList;

};


class FBXObject : public object3D<float>
{
private:
	Axis3D						axis;

public:
	float						testTime = 0.0f;
	float						yaw = 0.0f;
	float						pitch = 0.0f;
	float						roll = 0.0f;
	Vector3f					curPos;

	std::wstring				m_wstrNodeType;
	std::string					m_strNodeName;
	std::string					m_strDataName;
	std::vector<std::string>	m_strTargetName;

	FBXObject*					parent = nullptr;
	std::vector<FBXObject*>		child;
	std::vector<Material>		Materials;

	FBXAnimationSceneInfo		m_animationSceneInfo;
	std::vector<FBXAnimationTrack> m_animationTrackList;

	float						m_currentAnimationFrame = 0.0f;
	float						m_AnimationInverse = 1.0f;

	ConstantBufferData_Bone		m_CBData_Bone;
	std::vector<SkinningData> SkinningList;
	std::map<std::string, Matrix4x4> BindPoseMap;
	std::map<std::string, int> BindPoseKeyStringToIdxMap;
	std::map<int, std::string> BindPoseIdxToKeyStringMap;

public:
	virtual bool				initialize() override;
	virtual bool				initializeVertexList() override;
	virtual bool				initializeIndexList() override;
	virtual bool				render() override;
	virtual bool				frame(float _dt) override;
	virtual bool				setMatrix(Matrix4x4* _world, Matrix4x4* _view, Matrix4x4* _proj) override;

public:
	virtual bool				rotationYawPitchRoll(float _yaw, float _pitch, float _roll);
	virtual Matrix4x4			interpolation(float _frame);

};