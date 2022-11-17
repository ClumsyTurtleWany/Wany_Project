#include "DXShader.hpp"
#include "DXSamplerState.hpp"

bool DXShader::initialize()
{
	if (isCreated)
	{
		return false;
	}

	if (m_pd3dDevice == nullptr)
	{
		OutputDebugString(L"WanyCore::DXShader::m_pd3dDevice is nullptr.\n");
		return false;
	}

	if (m_pImmediateContext == nullptr)
	{
		OutputDebugString(L"WanyCore::DXShader::m_pImmediateContext is nullptr.\n");
		return false;
	}

	if (FAILED(CreateConstantBuffer()))
	{
		OutputDebugString(L"WanyCore::DXShader::Failed Create Constant Buffer.\n");
		return false;
	}

	if (FAILED(CreateVertexBuffer()))
	{
		OutputDebugString(L"WanyCore::DXShader::Failed Create Vertex Buffer.\n");
		return false;
	}

	if (FAILED(CreateIndexBuffer()))
	{
		OutputDebugString(L"WanyCore::DXShader::Failed Create Index Buffer.\n");
		return false;
	}

	if (FAILED(CreateVertexSharder()))
	{
		OutputDebugString(L"WanyCore::DXShader::Failed Create Vertex Shader.\n");
		return false;
	}

	if (FAILED(CreatePixelSharder()))
	{
		OutputDebugString(L"WanyCore::DXShader::Failed Create Pixel Shader.\n");
		return false;
	}

	if (FAILED(CreateVertexLayout()))
	{
		OutputDebugString(L"WanyCore::DXShader::Failed Create Vertex Layout.\n");
		return false;
	}

	isCreated = true;

	return true;
}

bool DXShader::frame()
{
	if (!isCreated)
	{
		return false;
	}

	return true;
}

bool DXShader::PreRender()
{
	if (!isCreated)
	{
		return false;
	}

	return true;
}

bool DXShader::render()
{
	if (!isCreated)
	{
		return false;
	}

	// GPU Update
	m_pImmediateContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);

	// Constant Data Update
	if ((m_pConstantBuffer != nullptr))
	{
		m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &m_ConstantData, 0, 0);
	}

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
	m_pImmediateContext->IASetPrimitiveTopology(m_Topology);

	// Texture - Pixel Shader�� Texture �ѱ�
	if (m_pTexture != nullptr)
	{
		ID3D11ShaderResourceView* resourceView = m_pTexture->getResourceView();
		m_pImmediateContext->PSSetShaderResources(0, 1, &resourceView); // �������� 0��

		// Alpha ���� (��� ���� - ���伥 ���� ���� ��ó��), �̰͵� ��Ƽ �ؽ��� �������̴�.
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

	// Draw ������ ȣ��Ǹ� ���� ���������� ������� Ÿ�� ������. ���� �� ���� ������ ��� ������
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

bool DXShader::release()
{
	if (!isCreated)
	{
		return false;
	}

	if (m_pVertexBuffer != nullptr)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	}

	if (m_pConstantBuffer != nullptr)
	{
		m_pConstantBuffer->Release();
		m_pConstantBuffer = nullptr;
	}

	if (m_pIndexBuffer != nullptr)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = nullptr;
	}

	if (m_pVertexLayout != nullptr)
	{
		m_pVertexLayout->Release();
		m_pVertexLayout = nullptr;
	}

	if (isCreateVS && (m_pVertexShader != nullptr))
	{
		m_pVertexShader->Release();
		m_pVertexShader = nullptr;
	}

	if (isCreatePS && (m_pPixelShader != nullptr))
	{
		m_pPixelShader->Release();
		m_pPixelShader = nullptr;
	}

	if (isCreateVSCode && (m_pVertexShaderCode != nullptr))
	{
		m_pVertexShaderCode->Release();
		m_pVertexShaderCode = nullptr;
	}
	
	if (isCreatePSCode && (m_pPixelShaderCode != nullptr))
	{
		m_pPixelShaderCode->Release();
		m_pPixelShaderCode = nullptr;
	}

	return true;
}

HRESULT DXShader::CreateVertexBuffer()
{
	//HRESULT result;
	// NDC ��ǥ�� ����
	// x: -1 ~ +1
	// y: -1 ~ +1
	// z: 0 ~ +1

	// Index Buffer ���� Vertex Buffer�� ��� �� ���� �簢���� ������� Triangle 2��.
	// Vertex 6���� ������ �ʿ�������, Index Buffer�� ����ϰ� �Ǹ� 4���� Vertex�� ��� ������ �ȴ�.
	//m_VertexList.assign(6, Vertex());
	//m_VertexList[0].pos = { -0.25f, +0.25f, 0.0f }; // p1-LT
	//m_VertexList[1].pos = { +0.25f, +0.25f, 0.0f }; // p2-RT
	//m_VertexList[2].pos = { -0.25f, -0.25f, 0.0f }; // p3-LB
	//m_VertexList[3].pos = { -0.25f, -0.25f, 0.0f }; // p4-LB
	//m_VertexList[4].pos = { +0.25f, +0.25f, 0.0f }; // p5-RT
	//m_VertexList[5].pos = { +0.25f, -0.25f, 0.0f }; // p6-RB

	//m_VertexList[0].color = { 1.0f, 0.0f, 0.0f, 0.0f }; // p1-LT
	//m_VertexList[1].color = { 1.0f, 0.0f, 0.0f, 0.0f }; // p2-RT
	//m_VertexList[2].color = { 1.0f, 0.0f, 0.0f, 0.0f }; // p3-LB
	//m_VertexList[3].color = { 1.0f, 0.0f, 0.0f, 0.0f }; // p4-LB
	//m_VertexList[4].color = { 1.0f, 0.0f, 0.0f, 0.0f }; // p5-RT
	//m_VertexList[5].color = { 1.0f, 0.0f, 0.0f, 0.0f }; // p6-RB

	//m_VertexList[0].texture = { 0.0f, 0.0f }; // p1-LT
	//m_VertexList[1].texture = { 1.0f, 0.0f }; // p2-RT
	//m_VertexList[2].texture = { 0.0f, 1.0f }; // p3-LB
	//m_VertexList[3].texture = { 0.0f, 1.0f }; // p4-LB
	//m_VertexList[4].texture = { 1.0f, 0.0f }; // p5-RT
	//m_VertexList[5].texture = { 1.0f, 1.0f }; // p6-RB

	//m_VertexList.assign(4, Vertex());
	//m_VertexList[0].pos = { -1.0f, +1.0f, 0.0f }; // p1-LT
	//m_VertexList[1].pos = { +1.0f, +1.0f, 0.0f }; // p2-RT
	//m_VertexList[2].pos = { -1.0f, -1.0f, 0.0f }; // p3-LB
	//m_VertexList[3].pos = { +1.0f, -1.0f, 0.0f }; // p4-LB

	//m_VertexList[0].color = { 1.0f, 0.0f, 0.0f, 0.0f }; // p1-LT
	//m_VertexList[1].color = { 1.0f, 0.0f, 0.0f, 0.0f }; // p2-RT
	//m_VertexList[2].color = { 1.0f, 0.0f, 0.0f, 0.0f }; // p3-LB
	//m_VertexList[3].color = { 1.0f, 0.0f, 0.0f, 0.0f }; // p4-LB

	//m_VertexList[0].texture = { 0.0f, 0.0f }; // p1-LT
	//m_VertexList[1].texture = { 1.0f, 0.0f }; // p2-RT
	//m_VertexList[2].texture = { 0.0f, 1.0f }; // p3-LB
	//m_VertexList[3].texture = { 1.0f, 1.0f }; // p4-RB

	initializeVertexList();

	// CreateBuffer() Param
	// D3D11_BUFFER_DESC* pDesc,
	// D3D11_SUBRESOURCE_DATA* pInitialData,
	// ID3D11Buffer** ppBuffer
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(Vertex) * static_cast<UINT>(m_VertexList.size()); // ����Ʈ �뷮
	desc.Usage = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���� �뵵, D3D11_USAGE_DEFAULT == GPU �޸𸮿� �Ҵ�.
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// desc.CPUAccessFlags = 0; // CPU���� ���� �ϰ� �� ���̳�, 0���� �ϸ� ó�� �Ҵ� �̿ܿ��� CPU�� �а� ���� �Ұ�.
	// desc.MiscFlags = 0; //
	// desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialData;
	ZeroMemory(&initialData, sizeof(initialData));
	initialData.pSysMem = &m_VertexList.at(0); // �迭�� �ƴϸ� �ý��� �޸𸮿� ��� �� �� ����. �׷��� �׳� �迭���� ���� vector ���.

	return m_pd3dDevice->CreateBuffer(
		&desc, // ���� �Ҵ� 
		&initialData, // �ʱ� �Ҵ�� ���۸� ü��� CPU �޸�, NULL�� ������ ������ �� ���� ��.
		&m_pVertexBuffer); // desc cpu flag�� 0���� �ؼ� �� ���ۿ� CPU�� ���� �� �� ����.

}

HRESULT DXShader::CreateIndexBuffer()
{
	// 2022-09-08 �߰�
	// ���� ���ۿ� ��� �ִ� �ε��� ��� ��� �Ѵ�.
	// Vertex Buffer ��� ó�� 0, 1, 2
	// 2, 1, 3 ����(�ð� ���� ����)�� �ε����� �־��ָ� ��.
	// �ε��� ���۸� �־��ָ� Vertex Buffer�� �پ��� ������ �ӵ��� �� ��������.

	initializeIndexList();

	// CreateBuffer() Param
	// D3D11_BUFFER_DESC* pDesc,
	// D3D11_SUBRESOURCE_DATA* pInitialData,
	// ID3D11Buffer** ppBuffer
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(DWORD) * static_cast<UINT>(m_IndexList.size()); // ����Ʈ �뷮
	desc.Usage = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���� �뵵, D3D11_USAGE_DEFAULT == GPU �޸𸮿� �Ҵ�.
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER; // �ε��� ���۸� ����ϰڴٴ� �÷���
	// desc.CPUAccessFlags = 0; // CPU���� ���� �ϰ� �� ���̳�, 0���� �ϸ� ó�� �Ҵ� �̿ܿ��� CPU�� �а� ���� �Ұ�.
	// desc.MiscFlags = 0; //
	// desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialData;
	ZeroMemory(&initialData, sizeof(initialData));
	initialData.pSysMem = &m_IndexList.at(0); // �迭�� �ƴϸ� �ý��� �޸𸮿� ��� �� �� ����. �׷��� �׳� �迭���� ���� vector ���.

	return m_pd3dDevice->CreateBuffer(
		&desc, // ���� �Ҵ� 
		&initialData, // �ʱ� �Ҵ�� ���۸� ü��� CPU �޸�, NULL�� ������ ������ �� ���� ��.
		&m_pIndexBuffer); // desc cpu flag�� 0���� �ؼ� �� ���ۿ� CPU�� ���� �� �� ����.

}

HRESULT DXShader::CreateConstantBuffer()
{
	initializeConstantData();

	// CreateBuffer() Param
	// D3D11_BUFFER_DESC* pDesc,
	// D3D11_SUBRESOURCE_DATA* pInitialData,
	// ID3D11Buffer** ppBuffer
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(ConstantBufferData) * 1; // ����Ʈ �뷮
	desc.Usage = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���� �뵵, D3D11_USAGE_DEFAULT == GPU �޸𸮿� �Ҵ�. D3D11_USAGE_DYNAMIC; //
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // �ε��� ���۸� ����ϰڴٴ� �÷���
	//desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // Test
	//desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initialData;
	ZeroMemory(&initialData, sizeof(initialData));
	initialData.pSysMem = &m_ConstantData; // �迭�� �ƴϸ� �ý��� �޸𸮿� ��� �� �� ����. �׷��� �׳� �迭���� ���� vector ���.

	return m_pd3dDevice->CreateBuffer(
		&desc, // ���� �Ҵ� 
		&initialData, // �ʱ� �Ҵ�� ���۸� ü��� CPU �޸�, NULL�� ������ ������ �� ���� ��.
		&m_pConstantBuffer);

	//// Test
	//return m_pd3dDevice->CreateBuffer(
	//	&desc, // ���� �Ҵ� 
	//	NULL, // �ʱ� �Ҵ�� ���۸� ü��� CPU �޸�, NULL�� ������ ������ �� ���� ��.
	//	&m_pConstantBuffer);
}

HRESULT DXShader::CreateVertexLayout()
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
		{"TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0} // 28 == float * 28 // Vertex�� Texture ���� ����Ʈ.
	};

	UINT NumElements = sizeof(InputElementDescs) / sizeof(InputElementDescs[0]);
	result = m_pd3dDevice->CreateInputLayout(InputElementDescs, NumElements, m_pVertexShaderCode->GetBufferPointer(), m_pVertexShaderCode->GetBufferSize(), &m_pVertexLayout);

	if (FAILED(result))
	{
		return result;
	}

	return result;
}

HRESULT DXShader::CreateVertexSharder()
{
	if (m_pVertexShaderCode == nullptr)
	{
		// ���� ���̾ƿ��� ���� ���̴��� ������ ������ �ִ�.
		// ���� ���̾ƿ� ���� �� ������ ���� ���̴� ������ �ʿ���. VertexShader.txt ����.
		// ���� ���� ���̴� �������� ���� �ʿ���. ���̴� �ȿ����� �����ڵ尡 �۵� ����.
		// D3DCompileFromFile()
		// LPCWSTR pFileName : ���� �̸�
		// D3D_SHADER_MACRO* pDefines
		// ID3DInclude* pInclude
		// LPCSTR pEntrypoint : ����� �Լ�(VertexShader.txt�� �ִ� �Լ�) �̸�
		// LPCSTR pTarget : �����Ϸ� ����(���̴� ���� ���� �ٸ�)
		// UINT Flags1
		// UINT Flags2
		// ID3DBlob** ppCode : ���(.obj ������ ���� �ּҿ�, ũ�⸦ ��ȯ ��.)
		// _Always_(_Outptr_opt_result_maybenull_ : Error Code
		std::wstring filepath = m_wstrVertexShaderFile.empty() ? m_wstrShaderFile : m_wstrVertexShaderFile;
		HRESULT result;
		ID3DBlob* pErrorCode = nullptr;
		result = D3DCompileFromFile(
			filepath.c_str(), //L"../../resource/shader/ShapeShader.txt",  //L"VertexShader.txt",
			NULL, NULL,
			"VS",
			"vs_5_0",
			0, 0,
			&m_pVertexShaderCode,
			&pErrorCode);

		if (FAILED(result))
		{
			if (pErrorCode != nullptr) // ���̴� ���Ͽ����� ������� �Ұ��� �ؼ� Error Code �޾ƿͼ� ó���ϴ°� ����.
			{
				OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
				pErrorCode->Release();
			}
			return result;
		}

		isCreateVSCode = true;	
	}

	if (m_pVertexShader == nullptr)
	{
		HRESULT result = m_pd3dDevice->CreateVertexShader(m_pVertexShaderCode->GetBufferPointer(), m_pVertexShaderCode->GetBufferSize(), NULL, &m_pVertexShader);

		if (FAILED(result))
		{
			return result;
		}

		isCreateVS = true;
		return result;
	}
	else
	{
		return S_OK;
	}
}

HRESULT DXShader::CreatePixelSharder()
{
	if (m_pPixelShaderCode == nullptr)
	{
		// Pixel Shader Create
		std::wstring filepath = m_wstrPixelShaderFile.empty() ? m_wstrShaderFile : m_wstrPixelShaderFile;
		HRESULT result;
		ID3DBlob* pErrorCode = nullptr; // 
		result = D3DCompileFromFile(
			filepath.c_str(), //L"../../resource/shader/ShapeShader.txt", //L"PixelShader.txt",
			NULL, NULL,
			"PS",
			"ps_5_0",
			0, 0,
			&m_pPixelShaderCode,
			&pErrorCode);

		if (FAILED(result))
		{
			if (pErrorCode != nullptr) // ���̴� ���Ͽ����� ������� �Ұ��� �ؼ� Error Code �޾ƿͼ� ó���ϴ°� ����.
			{
				OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
				pErrorCode->Release();
			}
		}

		isCreatePSCode = true;
	}

	if (m_pPixelShader == nullptr)
	{
		HRESULT result = m_pd3dDevice->CreatePixelShader(m_pPixelShaderCode->GetBufferPointer(), m_pPixelShaderCode->GetBufferSize(), NULL, &m_pPixelShader);

		if (FAILED(result))
		{
			return result;
		}

		isCreatePS = true;
		return result;
	}
	else
	{
		return S_OK;
	}
}

void DXShader::initializeVertexList()
{
	// Index Buffer ���� Vertex Buffer�� ��� �� ���� �簢���� ������� Triangle 2��.
	// Vertex 6���� ������ �ʿ�������, Index Buffer�� ����ϰ� �Ǹ� 4���� Vertex�� ��� ������ �ȴ�.
	//m_VertexList.assign(6, Vertex());
	//m_VertexList[0].pos = { -0.25f, +0.25f, 0.0f }; // p1-LT
	//m_VertexList[1].pos = { +0.25f, +0.25f, 0.0f }; // p2-RT
	//m_VertexList[2].pos = { -0.25f, -0.25f, 0.0f }; // p3-LB
	//m_VertexList[3].pos = { -0.25f, -0.25f, 0.0f }; // p4-LB
	//m_VertexList[4].pos = { +0.25f, +0.25f, 0.0f }; // p5-RT
	//m_VertexList[5].pos = { +0.25f, -0.25f, 0.0f }; // p6-RB

	//m_VertexList[0].color = { 1.0f, 0.0f, 0.0f, 0.0f }; // p1-LT
	//m_VertexList[1].color = { 1.0f, 0.0f, 0.0f, 0.0f }; // p2-RT
	//m_VertexList[2].color = { 1.0f, 0.0f, 0.0f, 0.0f }; // p3-LB
	//m_VertexList[3].color = { 1.0f, 0.0f, 0.0f, 0.0f }; // p4-LB
	//m_VertexList[4].color = { 1.0f, 0.0f, 0.0f, 0.0f }; // p5-RT
	//m_VertexList[5].color = { 1.0f, 0.0f, 0.0f, 0.0f }; // p6-RB

	//m_VertexList[0].texture = { 0.0f, 0.0f }; // p1-LT
	//m_VertexList[1].texture = { 1.0f, 0.0f }; // p2-RT
	//m_VertexList[2].texture = { 0.0f, 1.0f }; // p3-LB
	//m_VertexList[3].texture = { 0.0f, 1.0f }; // p4-LB
	//m_VertexList[4].texture = { 1.0f, 0.0f }; // p5-RT
	//m_VertexList[5].texture = { 1.0f, 1.0f }; // p6-RB

	m_VertexList.assign(4, Vertex());
	m_VertexList[0].pos = { -1.0f, +1.0f, 0.0f }; // p1-LT
	m_VertexList[1].pos = { +1.0f, +1.0f, 0.0f }; // p2-RT
	m_VertexList[2].pos = { -1.0f, -1.0f, 0.0f }; // p3-LB
	m_VertexList[3].pos = { +1.0f, -1.0f, 0.0f }; // p4-LB

	m_VertexList[0].color = { 1.0f, 1.0f, 1.0f, 1.0f }; // p1-LT
	m_VertexList[1].color = { 1.0f, 1.0f, 1.0f, 1.0f }; // p2-RT
	m_VertexList[2].color = { 1.0f, 1.0f, 1.0f, 1.0f }; // p3-LB
	m_VertexList[3].color = { 1.0f, 1.0f, 1.0f, 1.0f }; // p4-LB

	m_VertexList[0].texture = { 0.0f, 0.0f }; // p1-LT
	m_VertexList[1].texture = { 1.0f, 0.0f }; // p2-RT
	m_VertexList[2].texture = { 0.0f, 1.0f }; // p3-LB
	m_VertexList[3].texture = { 1.0f, 1.0f }; // p4-LB


	//m_VertexList[0].color = { 1.0f, 1.0f, 1.0f, 0.5f }; // p1-LT
	//m_VertexList[1].color = { 1.0f, 1.0f, 1.0f, 0.5f }; // p2-RT
	//m_VertexList[2].color = { 1.0f, 1.0f, 1.0f, 0.5f }; // p3-LB
	//m_VertexList[3].color = { 1.0f, 1.0f, 1.0f, 0.5f }; // p4-LB
}

void DXShader::initializeIndexList()
{
	// 2022-09-08 �߰�
	// ���� ���ۿ� ��� �ִ� �ε��� ��� ��� �Ѵ�.
	// Vertex Buffer ��� ó�� 0, 1, 2
	// 2, 1, 3 ����(�ð� ���� ����)�� �ε����� �־��ָ� ��.
	// �ε��� ���۸� �־��ָ� Vertex Buffer�� �پ��� ������ �ӵ��� �� ��������.

	// Rect
	m_IndexList.assign(6, 0);
	m_IndexList[0] = 0;
	m_IndexList[1] = 1;
	m_IndexList[2] = 2;
	m_IndexList[3] = 2;
	m_IndexList[4] = 1;
	m_IndexList[5] = 3;
}

void DXShader::initializeConstantData()
{
	m_ConstantData.matWorld.Identity();
	m_ConstantData.matView.Identity();
	m_ConstantData.matProj.Identity();

	m_ConstantData.matWorld = m_ConstantData.matWorld.Transpose();
	m_ConstantData.matView = m_ConstantData.matView.Transpose();
	m_ConstantData.matProj = m_ConstantData.matProj.Transpose();
}

void DXShader::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}

void DXShader::setTexture(DXTexture* _texture)
{
	m_pTexture = _texture;
}

void DXShader::setColor(const Vector4f& _color)
{
	for (auto& it : m_VertexList)
	{
		it.color = _color;
	}
}

void DXShader::setTextureMask(DXTexture* _texture)
{
	m_pTextureMask = _texture;
}

void DXShader::setShaderFile(std::wstring _file)
{
	m_wstrShaderFile = _file;
}

void DXShader::setVertexShaderFile(std::wstring _file)
{
	m_wstrVertexShaderFile = _file;
}

void DXShader::setPixelShaderFile(std::wstring _file)
{
	m_wstrPixelShaderFile = _file;
}

void DXShader::setTextureFile(std::wstring _file)
{
	m_wstrTextureFile = _file;
}

void DXShader::setTopology(D3D11_PRIMITIVE_TOPOLOGY _topology)
{
	m_Topology = _topology;
}

void DXShader::setCullMode(CullMode _mode)
{
	m_CullMode = _mode;
}

void DXShader::setVSCode(ID3DBlob* _VSCode)
{
	m_pVertexShaderCode = _VSCode;
}

void DXShader::setPSCode(ID3DBlob* _PSCode)
{
	m_pPixelShaderCode = _PSCode;
}

void DXShader::setVertexShader(ID3D11VertexShader* _VS)
{
	m_pVertexShader = _VS;
}

void DXShader::setPixelShader(ID3D11PixelShader* _PS)
{
	m_pPixelShader = _PS;
}

std::vector<Vertex>* DXShader::getVertexList()
{
	return &m_VertexList;
}

bool DXShader::updateVertexList(std::vector<Vertex>* _list)
{
	if (_list->empty())
	{
		return false;
	}

	if (m_VertexList.size() == _list->size())
	{
		m_VertexList.assign(_list->begin(), _list->end());
		if (m_pVertexBuffer != nullptr)
		{
			m_pImmediateContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
		}
	}
	else
	{
		m_VertexList.assign(_list->begin(), _list->end());

		if (m_pVertexBuffer != nullptr)
		{
			m_pVertexBuffer->Release();
			m_pVertexBuffer = nullptr;
		}

		// CreateBuffer() Param
		// D3D11_BUFFER_DESC* pDesc,
		// D3D11_SUBRESOURCE_DATA* pInitialData,
		// ID3D11Buffer** ppBuffer
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.ByteWidth = sizeof(Vertex) * static_cast<UINT>(m_VertexList.size()); // ����Ʈ �뷮
		desc.Usage = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���� �뵵, D3D11_USAGE_DEFAULT == GPU �޸𸮿� �Ҵ�.
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		// desc.CPUAccessFlags = 0; // CPU���� ���� �ϰ� �� ���̳�, 0���� �ϸ� ó�� �Ҵ� �̿ܿ��� CPU�� �а� ���� �Ұ�.
		// desc.MiscFlags = 0; //
		// desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initialData;
		ZeroMemory(&initialData, sizeof(initialData));
		initialData.pSysMem = &m_VertexList.at(0); // �迭�� �ƴϸ� �ý��� �޸𸮿� ��� �� �� ����. �׷��� �׳� �迭���� ���� vector ���.

		HRESULT rst = m_pd3dDevice->CreateBuffer(
			&desc, // ���� �Ҵ� 
			&initialData, // �ʱ� �Ҵ�� ���۸� ü��� CPU �޸�, NULL�� ������ ������ �� ���� ��.
			&m_pVertexBuffer); // desc cpu flag�� 0���� �ؼ� �� ���ۿ� CPU�� ���� �� �� ����.

		if (m_pVertexBuffer != nullptr)
		{
			m_pImmediateContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
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

bool DXShader::updateIndexList(std::vector<DWORD>* _list)
{
	if (_list->empty())
	{
		return false;
	}

	/*if (m_IndexList.size() == _list->size())
	{
		m_IndexList.assign(_list->begin(), _list->end());
		if (m_pIndexBuffer != nullptr)
		{
			m_pImmediateContext->UpdateSubresource(m_pIndexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
		}
	}
	else*/
	{
		m_IndexList.assign(_list->begin(), _list->end());

		if (m_pIndexBuffer != nullptr)
		{
			m_pIndexBuffer->Release();
			m_pIndexBuffer = nullptr;
		}

		// CreateBuffer() Param
		// D3D11_BUFFER_DESC* pDesc,
		// D3D11_SUBRESOURCE_DATA* pInitialData,
		// ID3D11Buffer** ppBuffer
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.ByteWidth = sizeof(DWORD) * static_cast<UINT>(m_IndexList.size()); // ����Ʈ �뷮
		desc.Usage = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���� �뵵, D3D11_USAGE_DEFAULT == GPU �޸𸮿� �Ҵ�.
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER; // �ε��� ���۸� ����ϰڴٴ� �÷���
		// desc.CPUAccessFlags = 0; // CPU���� ���� �ϰ� �� ���̳�, 0���� �ϸ� ó�� �Ҵ� �̿ܿ��� CPU�� �а� ���� �Ұ�.
		// desc.MiscFlags = 0; //
		// desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initialData;
		ZeroMemory(&initialData, sizeof(initialData));
		initialData.pSysMem = &m_IndexList.at(0); // �迭�� �ƴϸ� �ý��� �޸𸮿� ��� �� �� ����. �׷��� �׳� �迭���� ���� vector ���.

		HRESULT rst = m_pd3dDevice->CreateBuffer(
			&desc, // ���� �Ҵ� 
			&initialData, // �ʱ� �Ҵ�� ���۸� ü��� CPU �޸�, NULL�� ������ ������ �� ���� ��.
			&m_pIndexBuffer); // desc cpu flag�� 0���� �ؼ� �� ���ۿ� CPU�� ���� �� �� ����.

		if (FAILED(rst))
		{
			return false;
		}
		
		return true;

	}
}

bool DXShader::updateConstantData(ConstantBufferData* _data)
{
	if (_data == nullptr)
	{
		return false;
	}

	m_ConstantData.matWorld = _data->matWorld.Transpose();
	m_ConstantData.matView = _data->matView.Transpose();
	m_ConstantData.matProj = _data->matProj.Transpose();
	m_ConstantData.time1 = _data->time1;
	m_ConstantData.time2 = _data->time2;
	m_ConstantData.time3 = _data->time3;
	m_ConstantData.time4 = _data->time4;

	if ((m_pConstantBuffer != nullptr))
	{
		m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, nullptr, &m_ConstantData, 0, 0);
	}

	//D3D11_MAPPED_SUBRESOURCE MappedResource;
	//m_pImmediateContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD,	0, &MappedResource);
	//ConstantBufferData* pConstData = (ConstantBufferData*)MappedResource.pData;
	//pConstData->matWorld = _data->matWorld.Transpose();
	//pConstData->matView = _data->matView.Transpose();
	//pConstData->matProj = _data->matProj.Transpose();
	//m_pImmediateContext->Unmap(m_pConstantBuffer, 0);

	return true;
}

float DXShader::getTextureWidth()
{
	return m_pTexture->getWidth();
}

float DXShader::getTextureHeight()
{
	return m_pTexture->getHeight();
}