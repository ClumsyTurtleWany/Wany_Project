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

	// �ﰢ�� ������
	// 1) Input-Assember Stage

	// IASetVertexBuffers() Param
	// UINT StartSlot, : �������͸�
	// UINT NumBuffers, : ���� ����
	// ID3D11Buffer* const* ppVertexBuffers,
	// UINT* pStrides, : ���� 1���� ����Ʈ �뷮.
	// UINT* pOffsets  : ���� ���ۿ��� ��� ����(����Ʈ)
	UINT Strides = sizeof(Vertex); // ���� 1���� ����Ʈ �뷮
	UINT Offsets = 0; // ���� ���ۿ��� ��� ����(����Ʈ)
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Strides, &Offsets);

	// IASetInputLayout() Param
	m_pImmediateContext->IASetInputLayout(m_pVertexLayout);

	// 2) Vertex Shader Stage
	m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);

	// 3) Hull Shader Stage - ������ ��ŵ
	m_pImmediateContext->HSSetShader(NULL, NULL, 0);

	// 4) Domain Shader Stage - ������ ��ŵ
	m_pImmediateContext->DSSetShader(NULL, NULL, 0);

	// 5) Geometry Shader Stage - ������ ��ŵ
	m_pImmediateContext->GSSetShader(NULL, NULL, 0);

	// 6) Pixel Shader Stage
	m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);

	// �̷��� ���õ� �ִµ� ����Ʈ ������ �̹� ��� �־���.
	// �⺻������ Ʈ���̾ޱ۷� ��� ������ ����Ʈ Ȥ�� �簢�� ������ ��µ� ����.
	//m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// Border Draw�� ��ǻ� �̳��̶� Index List�� �ǵ帮�� ��.
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST); 

	// Texture - Pixel Shader�� Texture �ѱ�
	if (m_pTexture != nullptr)
	{
		ID3D11ShaderResourceView* resourceView = m_pTexture->getResourceView();
		m_pImmediateContext->PSSetShaderResources(0, 1, &resourceView); // �������� 0��
	}

	// Alpha ���� (��� ���� - ���伥 ���� ���� ��ó��)
	if (m_pTextureMask != nullptr)
	{
		ID3D11ShaderResourceView* resourceViewMask = m_pTextureMask->getResourceView();
		m_pImmediateContext->PSSetShaderResources(1, 1, &resourceViewMask); // �������� 1��
	}

	// Draw ����� ȣ��Ǹ� ���� ���������� ������� Ÿ�� ������. ���� �� ���� ������ ��� ������
	// ������ �ȵ������� ������ ����.
	// Vertex Buffer ��� �� �� ���
	if (m_pIndexBuffer == nullptr)
	{
		m_pImmediateContext->Draw(static_cast<UINT>(m_VertexList.size()), 0);
	}
	else
	{
		// Set Index Buffer
		m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// Index Buffer ��� �� �� DrawIndexed ��� �ؾ� ��.
		m_pImmediateContext->DrawIndexed(static_cast<UINT>(m_IndexList.size()), 0, 0);
	}

	return true;
}