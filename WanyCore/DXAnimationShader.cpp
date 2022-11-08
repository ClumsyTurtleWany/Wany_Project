#include "DXAnimationShader.hpp"

HRESULT DXAnimationShader::CreateVertexLayout()
{
	HRESULT result;

	// CreateInputLayout() Param
	// D3D11_INPUT_ELEMENT_DESC* pInputElementDescs : 쉐이더 처리 함수에 들어갈 in-out put 지정. Vertex의 각 요소로 나누어 넣으면 보기 편함.
	// UINT NumElements
	// void* pShaderBytecodeWithInputSignature  : 정점 쉐이더 처리 방법이 담긴 함수 포인터 (HLSL이나 txt 파일을 compile 해서 사용.)
	// SIZE_T BytecodeLength					: 정점 쉐이더 처리 방법이 담긴 함수의 크기 (HLSL이나 txt 파일을 compile 해서 사용.)
	// ID3D11InputLayout** ppInputLayout

	// D3D11_INPUT_ELEMENT_DESC InputElementDescs;
	// ZeroMemory(&InputElementDescs, sizeof(InputElementDescs));
	// InputElementDescs.SemanticName = "POSITION";
	// InputElementDescs.SemanticIndex = 0;
	// InputElementDescs.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	// InputElementDescs.InputSlot = 0;
	// InputElementDescs.AlignedByteOffset = 0; // 시작되는 바이트 위치
	// InputElementDescs.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	// InputElementDescs.InstanceDataStepRate = 0;

	D3D11_INPUT_ELEMENT_DESC InputElementDescs[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}, // 12 == float * 3 // Vertex의 Color 시작 바이트.
		{"TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0}, // 28 == float * 28 // Vertex의 Texture 시작 바이트.

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
	desc.ByteWidth = sizeof(IndexWeightData) * static_cast<UINT>(m_IWList.size()); // 바이트 용량
	desc.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼 용도, D3D11_USAGE_DEFAULT == GPU 메모리에 할당.
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// desc.CPUAccessFlags = 0; // CPU에서 접근 하게 할 것이냐, 0으로 하면 처음 할당 이외에는 CPU가 읽고 쓰기 불가.
	// desc.MiscFlags = 0; //
	// desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialData;
	ZeroMemory(&initialData, sizeof(initialData));
	initialData.pSysMem = &m_IWList.at(0); // 배열이 아니면 시스템 메모리에 들어 갈 수 없음. 그래서 그냥 배열보다 편한 vector 사용.

	return m_pd3dDevice->CreateBuffer(
		&desc, // 버퍼 할당 
		&initialData, // 초기 할당된 버퍼를 체우는 CPU 메모리, NULL로 넣으면 생성만 해 놓는 것.
		&m_pIWBuffer); // desc cpu flag를 0으로 해서 이 버퍼에 CPU는 접근 할 수 없음.
}

HRESULT DXAnimationShader::CreateConstantBuffer_Bone()
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(ConstantBufferData_Bone) * 1; // 바이트 용량
	desc.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼 용도, D3D11_USAGE_DEFAULT == GPU 메모리에 할당. D3D11_USAGE_DYNAMIC; //
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // 인덱스 버퍼를 사용하겠다는 플래그
	//desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // Test
	//desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initialData;
	ZeroMemory(&initialData, sizeof(initialData));
	initialData.pSysMem = &m_ConstantData_Bone; // 배열이 아니면 시스템 메모리에 들어 갈 수 없음. 그래서 그냥 배열보다 편한 vector 사용.

	return m_pd3dDevice->CreateBuffer(
		&desc, // 버퍼 할당 
		&initialData, // 초기 할당된 버퍼를 체우는 CPU 메모리, NULL로 넣으면 생성만 해 놓는 것.
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

	// 삼각형 랜더링
	// 1) Input-Assember Stage

	// IASetVertexBuffers() Param
	// UINT StartSlot, : 레지스터리
	// UINT NumBuffers, : 버퍼 갯수
	// ID3D11Buffer* const* ppVertexBuffers,
	// UINT* pStrides, : 정점 1개의 바이트 용량.
	// UINT* pOffsets  : 정점 버퍼에서 출발 지점(바이트)
	ID3D11Buffer* pBufferStream[2] = { m_pVertexBuffer, m_pIWBuffer }; // 멀티 스트림
	UINT Strides[2] = { sizeof(Vertex), sizeof(IndexWeightData) }; // 각 버퍼 데이터의 바이트 용량
	UINT Offsets[2] = { 0, 0 }; // 정점 버퍼에서 출발 지점(바이트)
	m_pImmediateContext->IASetVertexBuffers(0, 2, pBufferStream, Strides, Offsets);

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
	m_pImmediateContext->IASetPrimitiveTopology(m_Topology);

	// Texture - Pixel Shader에 Texture 넘김
	if (m_pTexture != nullptr)
	{
		ID3D11ShaderResourceView* resourceView = m_pTexture->getResourceView();
		m_pImmediateContext->PSSetShaderResources(0, 1, &resourceView); // 레지스터 0번

		// Alpha 제거 (배경 제거 - 포토샵 누끼 따는 것처럼)
		if (m_pTextureMask != nullptr)
		{
			ID3D11ShaderResourceView* resourceViewMask = m_pTextureMask->getResourceView();
			m_pImmediateContext->PSSetShaderResources(1, 1, &resourceViewMask); // 레지스터 1번
		}
	}

	// Blend State 적용.
	m_pImmediateContext->OMSetBlendState(DXSamplerState::pBlendSamplerState, 0, -1);

	// Rasterizer State 적용
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

	// Constant Buffer 적용
	if (m_pConstantBuffer != nullptr)
	{
		m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		//m_pImmediateContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	}

	if (m_pConstantBuffer_Bone != nullptr)
	{
		m_pImmediateContext->VSSetConstantBuffers(1, 1, &m_pConstantBuffer_Bone);
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
		desc.ByteWidth = sizeof(IndexWeightData) * static_cast<UINT>(m_IWList.size()); // 바이트 용량
		desc.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼 용도, D3D11_USAGE_DEFAULT == GPU 메모리에 할당.
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		// desc.CPUAccessFlags = 0; // CPU에서 접근 하게 할 것이냐, 0으로 하면 처음 할당 이외에는 CPU가 읽고 쓰기 불가.
		// desc.MiscFlags = 0; //
		// desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initialData;
		ZeroMemory(&initialData, sizeof(initialData));
		initialData.pSysMem = &m_IWList.at(0); // 배열이 아니면 시스템 메모리에 들어 갈 수 없음. 그래서 그냥 배열보다 편한 vector 사용.

		HRESULT rst = m_pd3dDevice->CreateBuffer(
			&desc, // 버퍼 할당 
			&initialData, // 초기 할당된 버퍼를 체우는 CPU 메모리, NULL로 넣으면 생성만 해 놓는 것.
			&m_pIWBuffer); // desc cpu flag를 0으로 해서 이 버퍼에 CPU는 접근 할 수 없음.

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
