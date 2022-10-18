#pragma once
#include "Define.hpp"
#include "DXDevice.hpp"

class DXSamplerState
{
public:
	static ID3D11SamplerState* pDefaultSamplerState;
	static ID3D11RasterizerState* pDefaultRSWireFrame;
	static ID3D11RasterizerState* pDefaultRSSolid;
	static ID3D11BlendState* pBlendSamplerState; // 투명도 조절

	static ID3D11DepthStencilState* pDefaultDepthStencil; // Less Equal
	static ID3D11DepthStencilState* pGreaterDepthStencil; // Greater

public:
	static bool setState(ID3D11Device* _pd3dDevice);
	static bool release();
};
