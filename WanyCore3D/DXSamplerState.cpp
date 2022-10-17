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
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; // �ֱ��� ���͸�. ���� u,v ���� ����� �� ����.
	//SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT; // �׽�Ʈ��
	
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP; // x �� // MIRROR_ONCE �� ���������� ���� ����. AMD ���� ����. �������� ONCE ��� CLAMP ����. 
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP; // y ��
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP; // z ��
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

	// Debug �� ������ ���÷�
	// Wire Frame: �ﰢ���� ������ ������ �Ѵ�.
	// Rasterizer State -> Pixel Shader�� �Ѱ��ش�.
	// �浹ó�� �� �� hitbox �����ִ� �뵵�� ����ϱ� ����.
	D3D11_RASTERIZER_DESC RSWireDesc;
	ZeroMemory(&RSWireDesc, sizeof(RSWireDesc));
	RSWireDesc.FillMode = D3D11_FILL_WIREFRAME; // Wire Frame, Solid
	RSWireDesc.CullMode = D3D11_CULL_BACK; //NONE; // ������ �������� �� ���ΰ� �޸��� �������� �� ���ΰ�. None == �� �� �� ����, Back == �ո� ����, Front �ڸ� ����.
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

	// Solid: ����Ʈ�� ���Ǵ� ���÷�. ������ Rasterizer State ���� �� �ֱ� ������ Solid�� �����Ǿ� ����.
	D3D11_RASTERIZER_DESC RSSolidDesc;
	ZeroMemory(&RSSolidDesc, sizeof(RSSolidDesc));
	RSSolidDesc.FillMode = D3D11_FILL_SOLID; // Wire Frame, Solid
	RSSolidDesc.CullMode = D3D11_CULL_BACK; //NONE; // ������ �������� �� ���ΰ� �޸��� �������� �� ���ΰ�. None == �� �� �� ����, Back == �ո� ����, Front �ڸ� ����.
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
	
	// ���(������: ����ۿ� �̹� �������� �Ǿ� �ִ� ���)�� ���� �ҽ�(���� ������ �Ϸ��� ��ü == �ȼ� ���̴� �ҽ�)�� ���´�.
	// �ȼ� ���̴� �ڿ� ȥ���� �ȴ�. (������ ������ ���ο��� Output-Merger Stage �ܰ迡 �ش� ��.)
	//BlendStateDesc.IndependentBlendEnable  = true; 

	// RenderTarget: �ִ� 8�� ���� �ѹ��� ������ ����. ����� 1���� ��� ��.
	// BlendEnable: ���� ���� ��� �� ���ΰ��� �÷���.
	BlendStateDesc.RenderTarget[0].BlendEnable = TRUE; 

	// RGB ������ ȥ���ϴ� ���(SrcBlend, DestBlend, BlendOp)
	BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // �ҽ��� ���İ�
	BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; // �ҽ��� ���İ��� ��
	BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD; // ���� ������ ����� ������ ����.
	// Alpha Blending �⺻ ����
	// Final Color = (Src Color * Src Alpha) + Dest Color * Inv Src Alpha(1.0f - SrcAlpha);
	// Alpha == 1.0f : ������, Alpha == 0.0f : ����, Alpha 0.0f ~ 1.0f : ������
	// Alpha == 1.0f, Final Color = (Src Color * 1.0f) + Dest Color * (1.0f - 1.0f) = Src Color;
	// Alpha == 0.0f, Final Color = (Src Color * 0.0f) + Dest Color * (1.0f - 0.0f) = Dest Color;
	
	// Alpha ������ ȥ���ϴ� ��� (SrcBlendAlpha, DestBlendAlpha, BlendOpAlpha, RenderTargetWriteMask)
	// Final Alpha = Src Alpha * 1.0f(D3D11_BLEND_ONE) + Dest Alpha * 0.0f(D3D11_BLEND_ZERO);
	BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	// RenderTargetWriteMask: ���� Ÿ���� ����ϴ� ����ũ ��Ʈ. ���� ���ϸ� ��� �ȵ�. �߿���.
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
