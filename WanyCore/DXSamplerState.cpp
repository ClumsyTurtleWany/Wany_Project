#include "DXSamplerState.hpp"

ID3D11SamplerState* DXSamplerState::pDefaultSamplerState = nullptr;
ID3D11RasterizerState* DXSamplerState::pDefaultRSWireFrame = nullptr;
ID3D11RasterizerState* DXSamplerState::pDefaultRSSolid = nullptr;
ID3D11BlendState* DXSamplerState::pBlendSamplerState = nullptr;

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
	//SamplerDesc.BorderColor[0] = 0.5f;
	//SamplerDesc.BorderColor[1] = 0.5f;
	//SamplerDesc.BorderColor[2] = 0.5f;
	//SamplerDesc.BorderColor[3] = 1.0f;
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
	RSWireDesc.CullMode = D3D11_CULL_BACK; //NONE; // 정면을 렌더하지 말 것인가 뒷면을 렌더하지 말 것인가. None == 앞 뒤 다 렌더, Back == 앞만 렌더, Front 뒤만 렌더.
	//RSWireDesc.FrontCounterClockwise;
	//RSWireDesc.DepthBias;
	//RSWireDesc.DepthBiasClamp;
	//RSWireDesc.SlopeScaledDepthBias;
	RSWireDesc.DepthClipEnable = TRUE;
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
	RSSolidDesc.CullMode = D3D11_CULL_BACK; //NONE; // 정면을 렌더하지 말 것인가 뒷면을 렌더하지 말 것인가. None == 앞 뒤 다 렌더, Back == 앞만 렌더, Front 뒤만 렌더.
	//RSSolidDesc.FrontCounterClockwise;
	//RSSolidDesc.DepthBias;
	//RSSolidDesc.DepthBiasClamp;
	//RSSolidDesc.SlopeScaledDepthBias;
	RSSolidDesc.DepthClipEnable = TRUE;
	//RSSolidDesc.ScissorEnable;
	//RSSolidDesc.MultisampleEnable;
	//RSSolidDesc.AntialiasedLineEnable;
	rst = _pd3dDevice->CreateRasterizerState(&RSSolidDesc, &pDefaultRSSolid);
	if (FAILED(rst))
	{
		OutputDebugString(L"WanyCore::DXSamplerState::Failed Create Rasterizer State Solid.\n");
		return false;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Blend State
	/////////////////////////////////////////////////////////////////////////////////////////////////

	D3D11_BLEND_DESC BlendStateDesc;
	ZeroMemory(&BlendStateDesc, sizeof(BlendStateDesc));
	//BlendStateDesc.AlphaToCoverageEnable;
	
	// 배경(목적지: 백버퍼에 이미 랜더링이 되어 있는 결과)과 현재 소스(지금 랜더링 하려는 객체 == 픽셀 쉐이더 소스)를 섞는다.
	// 픽셀 쉐이더 뒤에 혼합이 된다. (랜더링 파이프 라인에서 Output-Merger Stage 단계에 해당 됨.)
	//BlendStateDesc.IndependentBlendEnable  = true; 

	// RenderTarget: 최대 8개 까지 한번에 랜더링 가능. 현재는 1개만 사용 중.
	// BlendEnable: 알파 블렌딩 사용 할 것인가의 플래그.
	BlendStateDesc.RenderTarget[0].BlendEnable = TRUE; 

	// RGB 성분을 혼합하는 명령(SrcBlend, DestBlend, BlendOp)
	BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // 소스의 알파값
	BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; // 소스의 알파값의 역
	BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD; // 알파 블렌딩에 사용할 연산자 지정.
	// Alpha Blending 기본 공식
	// Final Color = (Src Color * Src Alpha) + Dest Color * Inv Src Alpha(1.0f - SrcAlpha);
	// Alpha == 1.0f : 불투명, Alpha == 0.0f : 투명, Alpha 0.0f ~ 1.0f : 반투명
	// Alpha == 1.0f, Final Color = (Src Color * 1.0f) + Dest Color * (1.0f - 1.0f) = Src Color;
	// Alpha == 0.0f, Final Color = (Src Color * 0.0f) + Dest Color * (1.0f - 0.0f) = Dest Color;
	
	// Alpha 성분을 혼합하는 명령 (SrcBlendAlpha, DestBlendAlpha, BlendOpAlpha, RenderTargetWriteMask)
	// Final Alpha = Src Alpha * 1.0f(D3D11_BLEND_ONE) + Dest Alpha * 0.0f(D3D11_BLEND_ZERO);
	BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	// RenderTargetWriteMask: 랜더 타겟을 출력하는 마스크 비트. 설정 안하면 출력 안됨. 중요함.
	BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	rst = _pd3dDevice->CreateBlendState(&BlendStateDesc, &pBlendSamplerState);
	if (FAILED(rst))
	{
		OutputDebugString(L"WanyCore::DXSamplerState::Failed Create Blend State Solid.\n");
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

	if (pBlendSamplerState != nullptr)
	{
		pBlendSamplerState->Release();
		pBlendSamplerState = nullptr;
	}

	return true;
}
