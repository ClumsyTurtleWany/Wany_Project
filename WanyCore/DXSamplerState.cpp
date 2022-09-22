#include "DXSamplerState.hpp"

ID3D11SamplerState* DXSamplerState::pDefaultSamplerState = nullptr;
ID3D11RasterizerState* DXSamplerState::pDefaultRSWireFrame = nullptr;
ID3D11RasterizerState* DXSamplerState::pDefaultRSSolid = nullptr;

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

	// Debug 시 유용한 샘플러
	// Wire Frame: 삼각형의 엣지만 랜더링 한다.
	// Rasterizer State -> Pixel Shader로 넘겨준다.
	// 충돌처리 할 때 hitbox 보여주는 용도로 사용하기 좋음.
	D3D11_RASTERIZER_DESC RSWireDesc;
	ZeroMemory(&RSWireDesc, sizeof(RSWireDesc));
	RSWireDesc.FillMode = D3D11_FILL_WIREFRAME; // Wire Frame, Solid
	RSWireDesc.CullMode = D3D11_CULL_NONE; // 정면을 뿌리지 말 것인가 뒷면을 뿌리지 말 것인가. 
	//RSWireDesc.FrontCounterClockwise;
	//RSWireDesc.DepthBias;
	//RSWireDesc.DepthBiasClamp;
	//RSWireDesc.SlopeScaledDepthBias;
	RSWireDesc.DepthClipEnable = true;
	//RSWireDesc.ScissorEnable;
	//RSWireDesc.MultisampleEnable;
	//RSWireDesc.AntialiasedLineEnable;
	rst = _pd3dDevice->CreateRasterizerState(&RSWireDesc, &pDefaultRSWireFrame);
	if (FAILED(rst))
	{
		OutputDebugString(L"WanyCore::DXSamplerState::Failed Create Rasterizer State Wire Frame.\n");
		return false;
	}

	// Solid: 디폴트로 사용되는 샘플러. 기존에 Rasterizer State 셋팅 해 주기 전에는 Solid로 설정되어 있음.
	D3D11_RASTERIZER_DESC RSSolidDesc;
	ZeroMemory(&RSSolidDesc, sizeof(RSSolidDesc));
	RSSolidDesc.FillMode = D3D11_FILL_SOLID; // Wire Frame, Solid
	RSSolidDesc.CullMode = D3D11_CULL_NONE; // 정면을 뿌리지 말 것인가 뒷면을 뿌리지 말 것인가. 
	//RSSolidDesc.FrontCounterClockwise;
	//RSSolidDesc.DepthBias;
	//RSSolidDesc.DepthBiasClamp;
	//RSSolidDesc.SlopeScaledDepthBias;
	RSSolidDesc.DepthClipEnable = true;
	//RSSolidDesc.ScissorEnable;
	//RSSolidDesc.MultisampleEnable;
	//RSSolidDesc.AntialiasedLineEnable;
	rst = _pd3dDevice->CreateRasterizerState(&RSSolidDesc, &pDefaultRSSolid);
	if (FAILED(rst))
	{
		OutputDebugString(L"WanyCore::DXSamplerState::Failed Create Rasterizer State Solid.\n");
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

	if (pDefaultRSWireFrame != nullptr)
	{
		pDefaultRSWireFrame->Release();
		pDefaultRSWireFrame = nullptr;
	}

	if (pDefaultRSSolid != nullptr)
	{
		pDefaultRSSolid->Release();
		pDefaultRSSolid = nullptr;
	}

	return true;
}
