#pragma once
#include "Define.hpp"
#include "DXTextureManager.hpp"

enum class MaterialType
{
	BaseColor = (int)0,
	Metalic,
	Specular,
	Roughness,
	Anisotropy,
	Emissive,
	Opacity,
	OpacityMask,
	Normal,
	Tangent,
	WorldPositionOffset,
	SubSurfaceColor,
	AmbientOcclusion,
	Refraction,
	PixelDepthOffset,
};

class Material
{
	// ���̽� �÷�
	// ��Ż��
	// ����ŧ��
	// �����Ͻ�
	// �ִϼ�Ʈ����
	// �̹̽ú� �÷�
	// ���Ľ�Ƽ
	// ���Ľ�Ƽ ����ũ
	// �븻
	// ź��Ʈ
	// ���� ������ ������
	// ���꼭���̽� �÷�
	// �ں��Ʈ ��Ŭ����
	// ����
	// �ȼ� ���� ������
	// ���̵� ��

	std::map<MaterialType, DXTexture*> TextureMap;

	/*DXTexture* BaseColor;
	DXTexture* Metalic;
	DXTexture* Specular;
	DXTexture* Roughness;
	DXTexture* Anisotropy;
	DXTexture* Emissive;
	DXTexture* Opacity;
	DXTexture* OpacityMask;
	DXTexture* Normal;
	DXTexture* Tangent;
	DXTexture* WorldPositionOffset;
	DXTexture* SubSurfaceColor;
	DXTexture* AmbientOcclusion;
	DXTexture* Refraction;
	DXTexture* PixelDepthOffset;*/
	//DXTexture* ShadingModel;
	
};

class Mesh
{
	std::vector<Vertex> Vertices;

};