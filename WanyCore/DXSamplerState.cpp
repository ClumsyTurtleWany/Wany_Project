#include "DXSamplerState.hpp"

ID3D11SamplerState* DXSamplerState::pDefaultSamplerState = nullptr;

bool DXSamplerState::setState(ID3D11Device* _pd3dDevice)
{
	// Sampler State
	// D3D11_SAMPLER_DESC *pSamplerDesc
	// ID3D11SamplerState** ppSamplerState
	D3D11_SAMPLER_DESC SamplerDesc;
	ZeroMemory(&SamplerDesc, sizeof(D3D11_SAMPLER_DESC));
	// D3D11_FILTER Filter;
	// D3D11_TEXTURE_ADDRESS_MODE AddressU;
	// D3D11_TEXTURE_ADDRESS_MODE AddressV;
	// D3D11_TEXTURE_ADDRESS_MODE AddressW;
	// FLOAT MipLODBias;
	// UINT MaxAnisotropy;
	// D3D11_COMPARISON_FUNC ComparisonFunc;
	// FLOAT BorderColor[4];
	// FLOAT MinLOD;
	// FLOAT MaxLOD;
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; // 최근점 필터링. 현재 u,v 값에 가까운 값 넣음.
	//SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT; // 테스트용
	
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP; // x 축 // MIRROR_ONCE 는 지포스에서 지원 안함. AMD 에서 지원. 지포스는 ONCE 대신 CLAMP 실행. 
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP; // y 축
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP; // z 축
	SamplerDesc.BorderColor[0] = 0.5f;
	SamplerDesc.BorderColor[1] = 0.5f;
	SamplerDesc.BorderColor[2] = 0.5f;
	SamplerDesc.BorderColor[3] = 1.0f;
	HRESULT rst = _pd3dDevice->CreateSamplerState(&SamplerDesc, &pDefaultSamplerState);
	if (FAILED(rst))
	{
		OutputDebugString(L"WanyCore::DXSamplerState::Failed Create Sampler State.\n");
		return false;
	}
	return true;
}

bool DXSamplerState::release()
{
	if (pDefaultSamplerState != nullptr)
	{
		pDefaultSamplerState->Release();
		pDefaultSamplerState = nullptr;
	}

	return true;
}
