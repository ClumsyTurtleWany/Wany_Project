#include "DXShader.hpp"


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

bool DXShader::render()
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
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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

	if (m_pVertexShader != nullptr)
	{
		m_pVertexShader->Release();
		m_pVertexShader = nullptr;
	}

	if (m_pPixelShader != nullptr)
	{
		m_pPixelShader->Release();
		m_pPixelShader = nullptr;
	}

	if (m_pVertexShaderCode != nullptr)
	{
		m_pVertexShaderCode->Release();
		m_pVertexShaderCode = nullptr;
	}

	if (m_pPixelShaderCode != nullptr)
	{
		m_pPixelShaderCode->Release();
		m_pPixelShaderCode = nullptr;
	}

	return true;
}

HRESULT DXShader::CreateVertexBuffer()
{
	//HRESULT result;
	// NDC 좌표계 공간
	// x: -1 ~ +1
	// y: -1 ~ +1
	// z: 0 ~ +1

	// Index Buffer 없이 Vertex Buffer만 사용 할 때는 사각형을 만드려면 Triangle 2개.
	// Vertex 6개의 정보가 필요하지만, Index Buffer를 사용하게 되면 4개의 Vertex만 들고 있으면 된다.
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
	desc.ByteWidth = sizeof(Vertex) * static_cast<UINT>(m_VertexList.size()); // 바이트 용량
	desc.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼 용도, D3D11_USAGE_DEFAULT == GPU 메모리에 할당.
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// desc.CPUAccessFlags = 0; // CPU에서 접근 하게 할 것이냐, 0으로 하면 처음 할당 이외에는 CPU가 읽고 쓰기 불가.
	// desc.MiscFlags = 0; //
	// desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialData;
	ZeroMemory(&initialData, sizeof(initialData));
	initialData.pSysMem = &m_VertexList.at(0); // 배열이 아니면 시스템 메모리에 들어 갈 수 없음. 그래서 그냥 배열보다 편한 vector 사용.

	return m_pd3dDevice->CreateBuffer(
		&desc, // 버퍼 할당 
		&initialData, // 초기 할당된 버퍼를 체우는 CPU 메모리, NULL로 넣으면 생성만 해 놓는 것.
		&m_pVertexBuffer); // desc cpu flag를 0으로 해서 이 버퍼에 CPU는 접근 할 수 없음.

}

HRESULT DXShader::CreateIndexBuffer()
{
	// 2022-09-08 추가
	// 정점 버퍼에 들어 있는 인덱스 대로 출력 한다.
	// Vertex Buffer 출력 처럼 0, 1, 2
	// 2, 1, 3 순서(시계 방향 순서)의 인덱스를 넣어주면 됨.
	// 인덱스 버퍼를 넣어주면 Vertex Buffer가 줄어들기 때문에 속도가 더 빨라진다.

	initializeIndexList();

	// CreateBuffer() Param
	// D3D11_BUFFER_DESC* pDesc,
	// D3D11_SUBRESOURCE_DATA* pInitialData,
	// ID3D11Buffer** ppBuffer
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(DWORD) * static_cast<UINT>(m_IndexList.size()); // 바이트 용량
	desc.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼 용도, D3D11_USAGE_DEFAULT == GPU 메모리에 할당.
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER; // 인덱스 버퍼를 사용하겠다는 플래그
	// desc.CPUAccessFlags = 0; // CPU에서 접근 하게 할 것이냐, 0으로 하면 처음 할당 이외에는 CPU가 읽고 쓰기 불가.
	// desc.MiscFlags = 0; //
	// desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialData;
	ZeroMemory(&initialData, sizeof(initialData));
	initialData.pSysMem = &m_IndexList.at(0); // 배열이 아니면 시스템 메모리에 들어 갈 수 없음. 그래서 그냥 배열보다 편한 vector 사용.

	return m_pd3dDevice->CreateBuffer(
		&desc, // 버퍼 할당 
		&initialData, // 초기 할당된 버퍼를 체우는 CPU 메모리, NULL로 넣으면 생성만 해 놓는 것.
		&m_pIndexBuffer); // desc cpu flag를 0으로 해서 이 버퍼에 CPU는 접근 할 수 없음.

}

HRESULT DXShader::CreateVertexLayout()
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
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}, // 12 == float * 3 // Vertex의 Color 시작 바이트.
		{"TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0} // 28 == float * 28 // Vertex의 Texture 시작 바이트.
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
	// 정점 레이아웃은 정점 쉐이더와 밀접한 관련이 있다.
	// 정점 레이아웃 생성 시 사전에 정점 쉐이더 생성이 필요함. VertexShader.txt 참고.
	// 따라서 정점 쉐이더 컴파일이 먼저 필요함. 쉐이더 안에서는 유니코드가 작동 안함.
	// D3DCompileFromFile()
	// LPCWSTR pFileName : 파일 이름
	// D3D_SHADER_MACRO* pDefines
	// ID3DInclude* pInclude
	// LPCSTR pEntrypoint : 사용할 함수(VertexShader.txt에 있는 함수) 이름
	// LPCSTR pTarget : 컴파일러 버전(쉐이더 버전 별로 다름)
	// UINT Flags1
	// UINT Flags2
	// ID3DBlob** ppCode : 결과(.obj 파일의 시작 주소와, 크기를 반환 함.)
	// _Always_(_Outptr_opt_result_maybenull_ : Error Code
	HRESULT result;
	ID3DBlob* pErrorCode = nullptr;
	result = D3DCompileFromFile(
		m_wstrShaderFile.c_str(), //L"../../resource/shader/ShapeShader.txt",  //L"VertexShader.txt",
		NULL, NULL,
		"VS",
		"vs_5_0",
		0, 0,
		&m_pVertexShaderCode,
		&pErrorCode);

	if (FAILED(result))
	{
		if (pErrorCode != nullptr) // 쉐이더 파일에서는 디버깅이 불가능 해서 Error Code 받아와서 처리하는게 좋음.
		{
			OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
			pErrorCode->Release();
		}
		return result;
	}

	result = m_pd3dDevice->CreateVertexShader(m_pVertexShaderCode->GetBufferPointer(), m_pVertexShaderCode->GetBufferSize(), NULL, &m_pVertexShader);

	if (FAILED(result))
	{
		return result;
	}

	return result;
}

HRESULT DXShader::CreatePixelSharder()
{
	// Pixel Shader Create
	HRESULT result;
	ID3DBlob* pErrorCode = nullptr; // 
	result = D3DCompileFromFile(
		m_wstrShaderFile.c_str(), //L"../../resource/shader/ShapeShader.txt", //L"PixelShader.txt",
		NULL, NULL,
		"PS",
		"ps_5_0",
		0, 0,
		&m_pPixelShaderCode,
		&pErrorCode);

	if (FAILED(result))
	{
		if (pErrorCode != nullptr) // 쉐이더 파일에서는 디버깅이 불가능 해서 Error Code 받아와서 처리하는게 좋음.
		{
			OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
			pErrorCode->Release();
		}
		return result;
	}

	result = m_pd3dDevice->CreatePixelShader(m_pPixelShaderCode->GetBufferPointer(), m_pPixelShaderCode->GetBufferSize(), NULL, &m_pPixelShader);

	if (FAILED(result))
	{
		return result;
	}

	return result;
}

void DXShader::initializeVertexList()
{
	// Index Buffer 없이 Vertex Buffer만 사용 할 때는 사각형을 만드려면 Triangle 2개.
	// Vertex 6개의 정보가 필요하지만, Index Buffer를 사용하게 되면 4개의 Vertex만 들고 있으면 된다.
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
}

void DXShader::initializeIndexList()
{
	// 2022-09-08 추가
	// 정점 버퍼에 들어 있는 인덱스 대로 출력 한다.
	// Vertex Buffer 출력 처럼 0, 1, 2
	// 2, 1, 3 순서(시계 방향 순서)의 인덱스를 넣어주면 됨.
	// 인덱스 버퍼를 넣어주면 Vertex Buffer가 줄어들기 때문에 속도가 더 빨라진다.

	// Rect
	m_IndexList.assign(6, 0);
	m_IndexList[0] = 0;
	m_IndexList[1] = 1;
	m_IndexList[2] = 2;
	m_IndexList[3] = 2;
	m_IndexList[4] = 1;
	m_IndexList[5] = 3;	
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
	for (auto &it : m_VertexList)
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

std::vector<Vertex>* DXShader::getVertexList()
{
	return &m_VertexList;
}

float DXShader::getTextureWidth()
{
	return m_pTexture->getWidth();
}

float DXShader::getTextureHeight()
{
	return m_pTexture->getHeight();
}