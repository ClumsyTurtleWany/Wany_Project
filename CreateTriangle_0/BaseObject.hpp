#pragma once
#include "DXDevice.hpp"
#include "Define.hpp"
#include "Vector.hpp"

class BaseObject : public DXDevice
{
public:
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;

public:
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;

	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;

	ID3DBlob* m_pVertexShaderCode = nullptr;
	ID3DBlob* m_pPixelShaderCode = nullptr;

public:
	bool initialize();
	bool frame();
	bool render();
	bool release();

public:
	HRESULT CreateVertexBuffer();
	HRESULT CreateVertexLayout();
	HRESULT CreateVertexSharder();
	HRESULT CreatePixelSharder();

public:
	void setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context);
};

bool BaseObject::initialize()
{
	if (FAILED(CreateVertexBuffer()))
	{
		return false;
	}

	if (FAILED(CreateVertexSharder()))
	{
		return false;
	}

	if (FAILED(CreatePixelSharder()))
	{
		return false;
	}

	if (FAILED(CreateVertexLayout()))
	{
		return false;
	}

	return true;
}

bool BaseObject::frame()
{
	return true;
}

bool BaseObject::render()
{
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
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Draw 명령이 호출되면 위의 파이프라인 순서대로 타고 내려옴. 셋팅 할 때의 순서는 상관 없으나
	// 셋팅이 안되있으면 문제가 생김.
	m_pImmediateContext->Draw(6, 0);

	return true;
}

bool BaseObject::release()
{
	if (m_pVertexBuffer != nullptr)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
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

HRESULT BaseObject::CreateVertexBuffer()
{
	HRESULT result;
	// NDC 좌표계 공간
	// x: -1 ~ +1
	// y: -1 ~ +1
	// z: 0 ~ +1
	Vertex vertices[] =
	{
		// 반드시 시계 방향(앞면) 으로 구성해야 한다.
		// 시계 반대 방향(뒷면)은 랜더링 안함.
		// Position				// Color
		-0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f, 0.0f, // v0
		+0.5f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f, 0.0f, // v1
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f, 0.0f, // v2

		-0.5f, -0.0f, 0.0f,		1.0f, 0.0f, 0.0f, 0.0f, // v2
		+0.5f, 0.5f, 0.0f,		0.0f, 1.0f, 0.0f, 0.0f, // v1
		+0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f, 0.0f, // v4		
	};

	// CreateBuffer() Param
	// D3D11_BUFFER_DESC* pDesc,
	// D3D11_SUBRESOURCE_DATA* pInitialData,
	// ID3D11Buffer** ppBuffer
	UINT NumVertex = sizeof(vertices) / sizeof(vertices[0]);
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(Vertex) * NumVertex; // 바이트 용량
	desc.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼 용도, D3D11_USAGE_DEFAULT == GPU 메모리에 할당. 
	// D3D11_USAGE_DEFAULT = 0,
	// D3D11_USAGE_IMMUTABLE = 1,
	// D3D11_USAGE_DYNAMIC = 2,
	// D3D11_USAGE_STAGING = 3
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// desc.CPUAccessFlags = 0; // CPU에서 접근 하게 할 것이냐, 0으로 하면 처음 할당 이외에는 CPU가 읽고 쓰기 불가.
	// desc.MiscFlags = 0; //
	// desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialData;
	ZeroMemory(&initialData, sizeof(initialData));
	initialData.pSysMem = vertices;

	return m_pd3dDevice->CreateBuffer(
		&desc, // 버퍼 할당 
		&initialData, // 초기 할당된 버퍼를 체우는 CPU 메모리, NULL로 넣으면 생성만 해 놓는 것.
		&m_pVertexBuffer); // desc cpu flag를 0으로 해서 이 버퍼에 CPU는 접근 할 수 없음.

}

HRESULT BaseObject::CreateVertexLayout()
{
	HRESULT result;

	// CreateInputLayout() Param
	// D3D11_INPUT_ELEMENT_DESC* pInputElementDescs
	// UINT NumElements
	// void* pShaderBytecodeWithInputSignature : 정점 쉐이더
	// SIZE_T BytecodeLength
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
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}, // 12 == float * 3
	};

	UINT NumElements = sizeof(InputElementDescs) / sizeof(InputElementDescs[0]);
	result = m_pd3dDevice->CreateInputLayout(InputElementDescs, NumElements, m_pVertexShaderCode->GetBufferPointer(), m_pVertexShaderCode->GetBufferSize(), &m_pVertexLayout);

	if (FAILED(result))
	{
		return result;
	}

	return result;
}

HRESULT BaseObject::CreateVertexSharder()
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
		L"VertexShader.txt",
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

}

HRESULT BaseObject::CreatePixelSharder()
{
	// Pixel Shader Create
	HRESULT result;
	ID3DBlob* pErrorCode = nullptr; // 
	result = D3DCompileFromFile(
		L"PixelShader.txt",
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
}

void BaseObject::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}