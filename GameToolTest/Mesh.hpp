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
	// 베이스 컬러
	// 메탈릭
	// 스페큘러
	// 러프니스
	// 애니소트로피
	// 이미시브 컬러
	// 오파시티
	// 오파시티 마스크
	// 노말
	// 탄젠트
	// 월드 포지션 오프셋
	// 서브서페이스 컬러
	// 앰비언트 오클루전
	// 굴절
	// 픽셀 뎁스 오프셋
	// 셰이딩 모델

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