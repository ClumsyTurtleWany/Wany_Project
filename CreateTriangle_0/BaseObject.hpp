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
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Draw ����� ȣ��Ǹ� ���� ���������� ������� Ÿ�� ������. ���� �� ���� ������ ��� ������
	// ������ �ȵ������� ������ ����.
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
	// NDC ��ǥ�� ����
	// x: -1 ~ +1
	// y: -1 ~ +1
	// z: 0 ~ +1
	Vertex vertices[] =
	{
		// �ݵ�� �ð� ����(�ո�) ���� �����ؾ� �Ѵ�.
		// �ð� �ݴ� ����(�޸�)�� ������ ����.
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
	desc.ByteWidth = sizeof(Vertex) * NumVertex; // ����Ʈ �뷮
	desc.Usage = D3D11_USAGE_DEFAULT; // ������ �Ҵ� ��� ������ ���� �뵵, D3D11_USAGE_DEFAULT == GPU �޸𸮿� �Ҵ�. 
	// D3D11_USAGE_DEFAULT = 0,
	// D3D11_USAGE_IMMUTABLE = 1,
	// D3D11_USAGE_DYNAMIC = 2,
	// D3D11_USAGE_STAGING = 3
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// desc.CPUAccessFlags = 0; // CPU���� ���� �ϰ� �� ���̳�, 0���� �ϸ� ó�� �Ҵ� �̿ܿ��� CPU�� �а� ���� �Ұ�.
	// desc.MiscFlags = 0; //
	// desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialData;
	ZeroMemory(&initialData, sizeof(initialData));
	initialData.pSysMem = vertices;

	return m_pd3dDevice->CreateBuffer(
		&desc, // ���� �Ҵ� 
		&initialData, // �ʱ� �Ҵ�� ���۸� ü��� CPU �޸�, NULL�� ������ ������ �� ���� ��.
		&m_pVertexBuffer); // desc cpu flag�� 0���� �ؼ� �� ���ۿ� CPU�� ���� �� �� ����.

}

HRESULT BaseObject::CreateVertexLayout()
{
	HRESULT result;

	// CreateInputLayout() Param
	// D3D11_INPUT_ELEMENT_DESC* pInputElementDescs
	// UINT NumElements
	// void* pShaderBytecodeWithInputSignature : ���� ���̴�
	// SIZE_T BytecodeLength
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
		if (pErrorCode != nullptr) // ���̴� ���Ͽ����� ������� �Ұ��� �ؼ� Error Code �޾ƿͼ� ó���ϴ°� ����.
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
		if (pErrorCode != nullptr) // ���̴� ���Ͽ����� ������� �Ұ��� �ؼ� Error Code �޾ƿͼ� ó���ϴ°� ����.
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