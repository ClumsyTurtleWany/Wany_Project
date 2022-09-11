#include "DXShaderBorder.hpp"

void DXShaderBorder::initializeIndexList()
{
	// Rect Border - Line List
	m_IndexList.assign(8, 0);

	// Line1 - LT to RT
	m_IndexList[0] = 0;
	m_IndexList[1] = 1;

	// Line2 - RT to RB
	m_IndexList[2] = 1;
	m_IndexList[3] = 3;

	// Line3 - RB to LB
	m_IndexList[4] = 3;
	m_IndexList[5] = 2;

	// Line4 - LB to LT
	m_IndexList[6] = 2;
	m_IndexList[7] = 0;
	
}

bool DXShaderBorder::render()
{
	if (!isCreated)
	{
		return false;
	}

	// GPU Update
	m_pImmediateContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);

	// 삼각형 랜더링
	// 1) Input-Assember Stage

	// IASetVertexBuffers() Param
	// UINT StartSlot, : 레지스터리
	// UINT NumBuffers, : 버퍼 갯수
	// ID3D11Buffer* const* ppVertexBuffers,
	// UINT* pStrides, : 정점 1개의 바이트 용량.
	// UINT* pOffsets  : 정점 버퍼에서 출발 지점(바이트)
	UINT Strides = sizeof(Vertex); // 정점 1개의 바이트 용량
	UINT Offsets = 0; // 정점 버퍼에서 출발 지점(바이트)
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Strides, &Offsets);

	// IASetInputLayout() Param
	m_pImmediateContext->IASetInputLayout(m_pVertexLayout);

	// 2) Vertex Shader Stage
	m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);

	// 3) Hull Shader Stage - 지금은 스킵
	m_pImmediateContext->HSSetShader(NULL, NULL, 0);

	// 4) Domain Shader Stage - 지금은 스킵
	m_pImmediateContext->DSSetShader(NULL, NULL, 0);

	// 5) Geometry Shader Stage - 지금은 스킵
	m_pImmediateContext->GSSetShader(NULL, NULL, 0);

	// 6) Pixel Shader Stage
	m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);

	// 이러한 셋팅도 있는데 디폴트 값으로 이미 들어 있었다.
	// 기본적으로 트라이앵글로 출력 하지만 포인트 혹은 사각형 등으로 출력도 가능.
	//m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// Border Draw는 사실상 이놈이랑 Index List만 건드리면 됨.
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST); 

	// Texture - Pixel Shader에 Texture 넘김
	if (m_pTexture != nullptr)
	{
		ID3D11ShaderResourceView* resourceView = m_pTexture->getResourceView();
		m_pImmediateContext->PSSetShaderResources(0, 1, &resourceView); // 레지스터 0번
	}

	// Alpha 제거 (배경 제거 - 포토샵 누끼 따는 것처럼)
	if (m_pTextureMask != nullptr)
	{
		ID3D11ShaderResourceView* resourceViewMask = m_pTextureMask->getResourceView();
		m_pImmediateContext->PSSetShaderResources(1, 1, &resourceViewMask); // 레지스터 1번
	}

	// Draw 명령이 호출되면 위의 파이프라인 순서대로 타고 내려옴. 셋팅 할 때의 순서는 상관 없으나
	// 셋팅이 안되있으면 문제가 생김.
	// Vertex Buffer 출력 할 때 사용
	if (m_pIndexBuffer == nullptr)
	{
		m_pImmediateContext->Draw(static_cast<UINT>(m_VertexList.size()), 0);
	}
	else
	{
		// Set Index Buffer
		m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// Index Buffer 사용 할 땐 DrawIndexed 사용 해야 함.
		m_pImmediateContext->DrawIndexed(static_cast<UINT>(m_IndexList.size()), 0, 0);
	}

	return true;
}