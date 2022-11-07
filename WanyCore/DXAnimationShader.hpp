#pragma once
#include "DXShader.hpp"
#include "DXSamplerState.hpp"

struct ConstantBufferData_Bone
{
	Matrix4x4 matBone[255];

	ConstantBufferData_Bone()
	{
		for (int i = 0; i < 255; i++)
		{
			matBone[i].Identity();
		}
	}
};

struct IndexWeightData
{
	Vector4f index;
	Vector4f weight;

	IndexWeightData()
	{
		index = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
		weight = Vector4f(1.0f, 0.0f, 0.0f, 0.0f);
	}
};

class DXAnimationShader : public DXShader
{
private:
	// Index & Weight Buffer
	ID3D11Buffer*						m_pIWBuffer = nullptr;
	std::vector<IndexWeightData>		m_IWList;

	// Constant Buffer for Bone Matrix
	ID3D11Buffer*						m_pConstantBuffer_Bone = nullptr;
	ConstantBufferData_Bone				m_ConstantData_Bone;

protected:
	virtual HRESULT						CreateVertexLayout() override;

protected:
	virtual HRESULT						CreateIWBuffer();
	virtual HRESULT						CreateConstantBuffer_Bone();

protected:
	virtual void						initializeIWList();

public:
	virtual bool initialize() override;
	virtual bool render() override;
	virtual bool release() override;

public:
	virtual bool updateIWList(std::vector<IndexWeightData>* _list);
	virtual bool updateConstantBuffer_Bone(ConstantBufferData_Bone* _data);
};