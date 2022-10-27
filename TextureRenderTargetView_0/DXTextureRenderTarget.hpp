#pragma once
#include "DXShaderManager.hpp"

class DXTextureRenderTarget
{
private:
	// Device
	ID3D11Device*			m_pd3dDevice = nullptr;
	ID3D11DeviceContext*	m_pImmediateContext = nullptr;

	// Texture Render Target View
	D3D11_VIEWPORT			m_viewPort;

	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
	DXTexture*				m_pTexture = nullptr;
	
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
	ID3D11Texture2D*		m_pDSTexture = nullptr;

	// For Save Prev View Infomation.
	ID3D11RenderTargetView* m_pOldRenderTargetView = nullptr;
	ID3D11DepthStencilView* m_pOldDepthStencilView = nullptr;
	D3D11_VIEWPORT			m_OldViewPort[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];

	// For Render
	DXShader*				m_pShader = nullptr;

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
	bool create(float _width, float _height);
	bool begin();
	bool render();
	bool end();
	bool release();

	void setOldRTV(ID3D11RenderTargetView* _pRTV);
	void setOldDSV(ID3D11DepthStencilView* _pDSV);
	void setOldVP(D3D11_VIEWPORT _vp);
};