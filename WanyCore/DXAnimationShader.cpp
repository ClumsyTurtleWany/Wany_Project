#include "DXAnimationShader.hpp"

HRESULT DXAnimationShader::CreateVertexLayout()
{
	HRESULT result;

	// CreateInputLayout() Param
	// D3D11_INPUT_ELEMENT_DESC* pInputElementDescs : ���̴� ó�� �Լ��� �� in-out put ����. Vertex�� �� ��ҷ� ������ ������ ���� ����.
	// UINT NumElements
	// void* pShaderBytecodeWithInputSignature  : ���� ���̴� ó�� ����� ��� �Լ� ������ (HLSL�̳� txt ������ compile �ؼ� ���.)
	// SIZE_T BytecodeLength					: ���� ���̴� ó�� ����� ��� �Լ��� ũ�� (HLSL�̳� txt ������ compile �ؼ� ���.)
	// ID3D11InputLayout** ppInputLayout

	// D3D11_INPUT_ELEMENT_DESC InputElementDescs;
	// ZeroMemory(&InputElementDescs, sizeof(InputElementDescs));
	// InputElementDescs.SemanticName = "POSITION";
	// InputElementDescs.SemanticIndex = 0;
	// InputElementDescs.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	// InputElementDescs.InputSlot = 0;
	// InputElementDescs.AlignedByteOffset = 0; // ���۵Ǵ� ����Ʈ ��ġ
	// InputElementDescs.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	// InputElementDescs.InstanceDataStepRate = 0;

	D3D11_INPUT_ELEMENT_DESC InputElementDescs[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}, // 12 == float * 3 // Vertex�� Color ���� ����Ʈ.
		{"TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0}, // 28 == float * 28 // Vertex�� Texture ���� ����Ʈ.

		{"INDEX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	UINT NumElements = sizeof(InputElementDescs) / sizeof(InputElementDescs[0]);
	result = m_pd3dDevice->CreateInputLayout(InputElementDescs, NumElements, m_pVertexShaderCode->GetBufferPointer(), m_pVertexShaderCode->GetBufferSize(), &m_pVertexLayout);

	if (FAILED(result))
	{
		return result;
	}

	return result;
}

HRESULT DXAnimationShader::CreateIWBuffer()
{
	initializeIWList();

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(IndexWeightData) * static_cast<UINT>(m_IWList.size()); // ����Ʈ �뷮
	desc.Usage = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���� �뵵, D3D11_USAGE_DEFAULT == GPU �޸𸮿� �Ҵ�.
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// desc.CPUAccessFlags = 0; // CPU���� ���� �ϰ� �� ���̳�, 0���� �ϸ� ó�� �Ҵ� �̿ܿ��� CPU�� �а� ���� �Ұ�.
	// desc.MiscFlags = 0; //
	// desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialData;
	ZeroMemory(&initialData, sizeof(initialData));
	initialData.pSysMem = &m_IWList.at(0); // �迭�� �ƴϸ� �ý��� �޸𸮿� ��� �� �� ����. �׷��� �׳� �迭���� ���� vector ���.

	return m_pd3dDevice->CreateBuffer(
		&desc, // ���� �Ҵ� 
		&initialData, // �ʱ� �Ҵ�� ���۸� ü��� CPU �޸�, NULL�� ������ ������ �� ���� ��.
		&m_pIWBuffer); // desc cpu flag�� 0���� �ؼ� �� ���ۿ� CPU�� ���� �� �� ����.
}

HRESULT DXAnimationShader::CreateConstantBuffer_Bone()
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(ConstantBufferData_Bone) * 1; // ����Ʈ �뷮
	desc.Usage = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���� �뵵, D3D11_USAGE_DEFAULT == GPU �޸𸮿� �Ҵ�. D3D11_USAGE_DYNAMIC; //
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // �ε��� ���۸� ����ϰڴٴ� �÷���
	//desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // Test
	//desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initialData;
	ZeroMemory(&initialData, sizeof(initialData));
	initialData.pSysMem = &m_ConstantData_Bone; // �迭�� �ƴϸ� �ý��� �޸𸮿� ��� �� �� ����. �׷��� �׳� �迭���� ���� vector ���.

	return m_pd3dDevice->CreateBuffer(
		&desc, // ���� �Ҵ� 
		&initialData, // �ʱ� �Ҵ�� ���۸� ü��� CPU �޸�, NULL�� ������ ������ �� ���� ��.
		&m_pConstantBuffer_Bone);
}

void DXAnimationShader::initializeIWList()
{
	m_IWList.resize(6);
}

bool DXAnimationShader::initialize()
{
	if (FAILED(CreateIWBuffer()))
	{
		OutputDebugString(L"WanyCore::DXAnimationShader::Failed Create Index & Weight Buffer.\n");
		return false;
	}

	if (FAILED(CreateConstantBuffer_Bone()))
	{
		OutputDebugString(L"WanyCore::DXAnimationShader::Failed Create Bone Constant Buffer.\n");
		return false;
	}

	DXShader::initialize();
	
	return true;
}

bool DXAnimationShader::render()
{
	if (!isCreated)
	{
		return false;
	}

	// GPU Update
	m_pImmediateContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
	m_pImmediateContext->UpdateSubresource(m_pIWBuffer, 0, NULL, &m_IWList.at(0), 0, 0);

	// Constant Data Update
	if ((m_pConstantBuffer != nullptr))
	{
		m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &m_ConstantData, 0, 0);
	}

	if ((m_pConstantBuffer_Bone != nullptr))
	{
		m_pImmediateContext->UpdateSubresource(m_pConstantBuffer_Bone, 0, NULL, &m_ConstantData_Bone, 0, 0);
	}

	// �ﰢ�� ������
	// 1) Input-Assember Stage

	// IASetVertexBuffers() Param
	// UINT StartSlot, : �������͸�
	// UINT NumBuffers, : ���� ����
	// ID3D11Buffer* const* ppVertexBuffers,
	// UINT* pStrides, : ���� 1���� ����Ʈ �뷮.
	// UINT* pOffsets  : ���� ���ۿ��� ��� ����(����Ʈ)
	ID3D11Buffer* pBufferStream[2] = { m_pVertexBuffer, m_pIWBuffer }; // ��Ƽ ��Ʈ��
	UINT Strides[2] = { sizeof(Vertex), sizeof(IndexWeightData) }; // �� ���� �������� ����Ʈ �뷮
	UINT Offsets[2] = { 0, 0 }; // ���� ���ۿ��� ��� ����(����Ʈ)
	m_pImmediateContext->IASetVertexBuffers(0, 2, pBufferStream, Strides, Offsets);

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
	m_pImmediateContext->IASetPrimitiveTopology(m_Topology);

	// Texture - Pixel Shader�� Texture �ѱ�
	if (m_pTexture != nullptr)
	{
		ID3D11ShaderResourceView* resourceView = m_pTexture->getResourceView();
		m_pImmediateContext->PSSetShaderResources(0, 1, &resourceView); // �������� 0��

		// Alpha ���� (��� ���� - ���伥 ���� ���� ��ó��)
		if (m_pTextureMask != nullptr)
		{
			ID3D11ShaderResourceView* resourceViewMask = m_pTextureMask->getResourceView();
			m_pImmediateContext->PSSetShaderResources(1, 1, &resourceViewMask); // �������� 1��
		}
	}

	// Blend State ����.
	m_pImmediateContext->OMSetBlendState(DXSamplerState::pBlendSamplerState, 0, -1);

	// Rasterizer State ����
	ID3D11RasterizerState* pOldRasterizerState = nullptr;
	m_pImmediateContext->RSGetState(&pOldRasterizerState);
	D3D11_RASTERIZER_DESC RSDesc;
	pOldRasterizerState->GetDesc(&RSDesc);
	if (RSDesc.FillMode == D3D11_FILL_WIREFRAME)
	{
		if (m_CullMode == CullMode::None)
		{
			m_pImmediateContext->RSSetState(DXSamplerState::pRSWireFrame_CullNone);
		}
		else if (m_CullMode == CullMode::Front)
		{
			m_pImmediateContext->RSSetState(DXSamplerState::pRSWireFrame_CullFront);
		}
		else
		{
			m_pImmediateContext->RSSetState(DXSamplerState::pDefaultRSWireFrame);
		}
	}
	else
	{
		if (m_CullMode == CullMode::None)
		{
			m_pImmediateContext->RSSetState(DXSamplerState::pRSSolid_CullNone);
		}
		else if (m_CullMode == CullMode::Front)
		{
			m_pImmediateContext->RSSetState(DXSamplerState::pRSSolid_CullFront);
		}
		else
		{
			m_pImmediateContext->RSSetState(DXSamplerState::pDefaultRSSolid);
		}
	}

	// Constant Buffer ����
	if (m_pConstantBuffer != nullptr)
	{
		m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		//m_pImmediateContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	}

	if (m_pConstantBuffer_Bone != nullptr)
	{
		m_pImmediateContext->VSSetConstantBuffers(1, 1, &m_pConstantBuffer_Bone);
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

	m_pImmediateContext->RSSetState(pOldRasterizerState);
	pOldRasterizerState->Release();

	return true;
}

bool DXAnimationShader::release()
{
	DXShader::release();

	if (m_pIWBuffer != nullptr)
	{
		m_pIWBuffer->Release();
		m_pIWBuffer = nullptr;
	}

	if (m_pConstantBuffer_Bone != nullptr)
	{
		m_pConstantBuffer_Bone->Release();
		m_pConstantBuffer_Bone = nullptr;
	}

	return true;
}

bool DXAnimationShader::updateIWList(std::vector<IndexWeightData>* _list)
{
	if (_list->empty())
	{
		return false;
	}

	if (m_IWList.size() == _list->size())
	{
		m_IWList.assign(_list->begin(), _list->end());
		if (m_pVertexBuffer != nullptr)
		{
			m_pImmediateContext->UpdateSubresource(m_pIWBuffer, 0, NULL, &m_IWList.at(0), 0, 0);
		}
	}
	else
	{
		m_IWList.assign(_list->begin(), _list->end());

		if (m_pIWBuffer != nullptr)
		{
			m_pIWBuffer->Release();
			m_pIWBuffer = nullptr;
		}

		// CreateBuffer() Param
		// D3D11_BUFFER_DESC* pDesc,
		// D3D11_SUBRESOURCE_DATA* pInitialData,
		// ID3D11Buffer** ppBuffer
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.ByteWidth = sizeof(IndexWeightData) * static_cast<UINT>(m_IWList.size()); // ����Ʈ �뷮
		desc.Usage = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���� �뵵, D3D11_USAGE_DEFAULT == GPU �޸𸮿� �Ҵ�.
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		// desc.CPUAccessFlags = 0; // CPU���� ���� �ϰ� �� ���̳�, 0���� �ϸ� ó�� �Ҵ� �̿ܿ��� CPU�� �а� ���� �Ұ�.
		// desc.MiscFlags = 0; //
		// desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initialData;
		ZeroMemory(&initialData, sizeof(initialData));
		initialData.pSysMem = &m_IWList.at(0); // �迭�� �ƴϸ� �ý��� �޸𸮿� ��� �� �� ����. �׷��� �׳� �迭���� ���� vector ���.

		HRESULT rst = m_pd3dDevice->CreateBuffer(
			&desc, // ���� �Ҵ� 
			&initialData, // �ʱ� �Ҵ�� ���۸� ü��� CPU �޸�, NULL�� ������ ������ �� ���� ��.
			&m_pIWBuffer); // desc cpu flag�� 0���� �ؼ� �� ���ۿ� CPU�� ���� �� �� ����.

		if (m_pIWBuffer != nullptr)
		{
			m_pImmediateContext->UpdateSubresource(m_pIWBuffer, 0, NULL, &m_IWList.at(0), 0, 0);
		}

		if (FAILED(rst))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

bool DXAnimationShader::updateConstantBuffer_Bone(ConstantBufferData_Bone* _data)
{
	for (int idx = 0; idx < 255; idx++)
	{
		m_ConstantData_Bone.matBone[idx] = _data->matBone[idx];
	}
	return true;
}
