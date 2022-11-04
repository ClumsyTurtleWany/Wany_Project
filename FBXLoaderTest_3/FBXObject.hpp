#pragma once
#include "Object.hpp"
#include "NewObject.hpp"

struct FBXAnimationTrack
{
	UINT frame;
	Matrix4x4 matAnimation; // self * parent
	Matrix4x4 matSelfAnimation;  // matAnimation * inv(Parent)
	Vector3f translation;
	Vector4f rotation; // Quaternion
	Vector3f scale;
};

struct FBXAnimationData
{
	UINT StartFrame;
	UINT EndFrame;
	float TickPerFrame = 160.0f;
	float FrameSpeed = 30.0f;
};

struct Material
{
	DXShader* Shader = nullptr;
	std::vector<Vertex> VertexList;
	std::vector<DWORD> IndexList;

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

	void push_back(const Vertex& _vertex)
	{
		VertexList.push_back(_vertex);
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
		if (DXShaderManager::getInstance()->Load(ShaderID, ShaderType::Object3D))
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
	std::vector<Material> MaterialList;
	void render()
	{
		for (size_t idx = 0; idx < MaterialList.size(); idx++)
		{
			MaterialList[idx].render();
		}
	}
};

struct Mesh
{
	std::vector<Layer> LayerList;

	void render()
	{
		for (size_t idx = 0; idx < LayerList.size(); idx++)
		{
			LayerList[idx].render();
		}
	}
};

struct Node
{
	Mesh mesh;

};

class FBXObject : public object3D<float>
{
private:
	Axis3D axis;

public:
	float testTime = 0.0f;
	float yaw = 0.0f;
	float pitch = 0.0f;
	float roll = 0.0f;
	Vector3f curPos;

	std::wstring m_wstrNodeType;
	std::string m_strNodeName;
	std::string m_strDataName;
	std::vector<std::string> m_strTargetName;

	FBXObject* parent = nullptr;
	std::vector<FBXObject*> child;
	std::vector<Material> Materials;

public:
	virtual bool initialize() override;
	virtual bool initializeVertexList() override;
	virtual bool initializeIndexList() override;
	virtual bool render() override;
	virtual bool frame(float _dt) override;
	virtual bool setMatrix(Matrix4x4* _world, Matrix4x4* _view, Matrix4x4* _proj) override;

public:
	virtual bool rotationYawPitchRoll(float _yaw, float _pitch, float _roll);

};