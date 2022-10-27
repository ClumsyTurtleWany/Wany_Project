#include "DXShaderManager.hpp"

void DXShaderManager::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}

bool DXShaderManager::LoadVSCode(VSCodeType _key, std::wstring _filename)
{
	ID3DBlob* pVSCode = getVSCode(_key);
	if (pVSCode == nullptr)
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
			_filename.c_str(), //L"../../resource/shader/ShapeShader.txt",  //L"VertexShader.txt",
			NULL, NULL,
			"VS",
			"vs_5_0",
			0, 0,
			&pVSCode,
			&pErrorCode);

		if (FAILED(result))
		{
			if (pErrorCode != nullptr) // 쉐이더 파일에서는 디버깅이 불가능 해서 Error Code 받아와서 처리하는게 좋음.
			{
				OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
				pErrorCode->Release();
			}
			return false;
		}
		else
		{
			m_pVertexShaderCodeMap.insert(std::make_pair(_key, pVSCode));
			return true;
		}
	}
	else
	{
		return true;
	}
}

bool DXShaderManager::LoadPSCode(PSCodeType _key, std::wstring _filename)
{
	ID3DBlob* pPSCode = getPSCode(_key);
	if (pPSCode == nullptr)
	{
		// Pixel Shader Create
		HRESULT result;
		ID3DBlob* pErrorCode = nullptr; // 
		result = D3DCompileFromFile(
			_filename.c_str(), //L"../../resource/shader/ShapeShader.txt", //L"PixelShader.txt",
			NULL, NULL,
			"PS",
			"ps_5_0",
			0, 0,
			&pPSCode,
			&pErrorCode);

		if (FAILED(result))
		{
			if (pErrorCode != nullptr) // 쉐이더 파일에서는 디버깅이 불가능 해서 Error Code 받아와서 처리하는게 좋음.
			{
				OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
				pErrorCode->Release();
			}
			return false;
		}
		else
		{
			m_pPixelShaderCodeMap.insert(std::make_pair(_key, pPSCode));
			return true;
		}
	}
	else
	{
		return true;
	}
}

bool DXShaderManager::Load(int _key, ShaderType _type)
{
	auto it = m_ShaderList.find(_key);
	if (it != m_ShaderList.end())
	{
		return false;
	}

	DXShader* newShader = nullptr;
	if (_type == ShaderType::Border)
	{
		newShader = new DXShaderBorder;
	}
	else
	{ 
		newShader = new DXShader;
	}
	
	newShader->setDevice(m_pd3dDevice, m_pImmediateContext);

	ID3DBlob* pVSCode = nullptr;
	ID3DBlob* pPSCode = nullptr;
	if (_type == ShaderType::Mask)
	{
		// 텍스처 출력 가능. 마스크 Discard
		newShader->setShaderFile(L"../include/core/HLSL/MaskShader.txt");
		pVSCode = getVSCode(VSCodeType::Texture);
		pPSCode = getPSCode(PSCodeType::Mask);
	}
	else if (_type == ShaderType::Texture)
	{
		// 텍스처 출력 가능.
		newShader->setShaderFile(L"../include/core/HLSL/TextureShader.txt");
		pVSCode = getVSCode(VSCodeType::Texture);
		pPSCode = getPSCode(PSCodeType::Texture);
	}
	else if (_type == ShaderType::Object3D)
	{
		// Constant Data 이용하여 쉐이더에서 매트릭스 계산. 텍스처 출력 가능.
		newShader->setShaderFile(L"../include/core/HLSL/Textured3D.txt");
		//newShader->setCreateConstantFlag(true);
		pVSCode = getVSCode(VSCodeType::ConstantBuffer);
		pPSCode = getPSCode(PSCodeType::Texture);
	}
	else if (_type == ShaderType::Axis3D)
	{
		// Constant Data 이용하여 쉐이더에서 매트릭스 계산.
		newShader->setShaderFile(L"../include/core/HLSL/DefaultObject.txt");
		//newShader->setCreateConstantFlag(true);
		pVSCode = getVSCode(VSCodeType::ConstantBuffer);
		pPSCode = getPSCode(PSCodeType::Normal);
	}
	else
	{
		// 다이렉트로 픽셀 뿌림. 텍스처 출력 불가.
		newShader->setShaderFile(L"../include/core/HLSL/ShapeShader.txt");
		pVSCode = getVSCode(VSCodeType::Texture);
		pPSCode = getPSCode(PSCodeType::Normal);
	}

	newShader->setVSCode(pVSCode);
	newShader->setPSCode(pPSCode);

	bool rst = newShader->initialize();
	if (!rst)
	{
		OutputDebugString(L"WanyCore::DXShaderManager::Failed Shader Initialize.\n");
		return false;
	}

	m_ShaderList.insert(std::make_pair(_key, newShader));

	return rst;
}

DXShader* DXShaderManager::getShader(int _key)
{
	auto it = m_ShaderList.find(_key);
	if (it != m_ShaderList.end())
	{
		return it->second;
	}
	return nullptr;
}

bool DXShaderManager::DeleteShader(int _key)
{
	auto it = m_ShaderList.find(_key);
	if (it != m_ShaderList.end())
	{
		DXShader* pShader = it->second;
		pShader->release();
		pShader = nullptr;
		m_ShaderList.erase(_key);
		return true;
	}
	return false;
}

ID3DBlob* DXShaderManager::getVSCode(VSCodeType _key)
{
	auto it = m_pVertexShaderCodeMap.find(_key);
	if (it != m_pVertexShaderCodeMap.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

ID3DBlob* DXShaderManager::getPSCode(PSCodeType _key)
{
	auto it = m_pPixelShaderCodeMap.find(_key);
	if (it != m_pPixelShaderCodeMap.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

bool DXShaderManager::initialize()
{
	// Load Vertex Shader Code.
	if (!LoadVSCode(VSCodeType::Texture, L"../include/core/HLSL/VS_Texture.hlsl"))
	{
		OutputDebugString(L"WanyCore::DXShaderManager::initialize::Failed Load VS Code(VS_Texture.hlsl).\n");
		return false;
	}

	if (!LoadVSCode(VSCodeType::ConstantBuffer, L"../include/core/HLSL/VS_ConstantBuffer.hlsl"))
	{
		OutputDebugString(L"WanyCore::DXShaderManager::initialize::Failed Load VS Code(VS_ConstantBuffer.hlsl).\n");
		return false;
	}

	// Load Pixel Shader Code.
	if (!LoadPSCode(PSCodeType::Normal, L"../include/core/HLSL/PS_Default.hlsl"))
	{
		OutputDebugString(L"WanyCore::DXShaderManager::initialize::Failed Load PS Code(PS_Default.hlsl).\n");
		return false;
	}

	if (!LoadPSCode(PSCodeType::Texture, L"../include/core/HLSL/PS_Texture.hlsl"))
	{
		OutputDebugString(L"WanyCore::DXShaderManager::initialize::Failed Load PS Code(PS_Texture.hlsl).\n");
		return false;
	}

	if (!LoadPSCode(PSCodeType::Mask, L"../include/core/HLSL/PS_Mask.hlsl"))
	{
		OutputDebugString(L"WanyCore::DXShaderManager::initialize::Failed Load PS Code(PS_Mask.hlsl).\n");
		return false;
	}
	return true;
}

bool DXShaderManager::frame()
{
	for (auto it : m_ShaderList)
	{
		it.second->frame();
	}
	return true;
}

bool DXShaderManager::render()
{
	for (auto it : m_ShaderList)
	{
		it.second->render();
	}
	return true;
}

bool DXShaderManager::release()
{
	if (!m_ShaderList.empty())
	{
		for (auto it : m_ShaderList)
		{
			DXShader* pShader = it.second;
			if (pShader != nullptr)
			{
				pShader->release();
				delete pShader;
			}
		}
		m_ShaderList.clear();
	}

	return true;
}