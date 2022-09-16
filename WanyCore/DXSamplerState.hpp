#pragma once
#include "Define.hpp"
#include "DXDevice.hpp"

class DXSamplerState
{
public:
	static ID3D11SamplerState* pDefaultSamplerState;
	static ID3D11BlendState* pBlendSamplerState; // ������ ����

public:
	static bool setState(ID3D11Device* _pd3dDevice);
	static bool release();
};