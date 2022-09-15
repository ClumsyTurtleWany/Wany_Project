#include "DXShaderBorderManager.hpp"

void DXShaderBorderManager::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}

bool DXShaderBorderManager::drawBorder(const Rect2f& _rect, const Vector4f& _color)
{
	RECT clientRect = g_pWindow->getClientRect();
	float mapWidth = clientRect.right - clientRect.left; // clientRectWidth;
	float mapHeight = clientRect.bottom - clientRect.top; // clientRectHeight;
	float mapWidth_Half = mapWidth * 0.5;
	float mapHeight_Half = mapHeight * 0.5;

	Rect_<float> rectNDC;
	rectNDC.LT.x = (_rect.LT.x - mapWidth_Half) / mapWidth_Half;
	rectNDC.LT.y = -(_rect.LT.y - mapHeight_Half) / mapHeight_Half;
	rectNDC.RB.x = (_rect.RB.x - mapWidth_Half) / mapWidth_Half;
	rectNDC.RB.y = -(_rect.RB.y - mapHeight_Half) / mapHeight_Half;

	// Vectex List
	std::vector<Vertex>* list = m_pBorderShader->getVertexList();
	list->at(0).pos = { rectNDC.LT.x, rectNDC.LT.y, 0.0f };
	list->at(1).pos = { rectNDC.RB.x, rectNDC.LT.y, 0.0f };
	list->at(2).pos = { rectNDC.LT.x, rectNDC.RB.y, 0.0f };
	list->at(3).pos = { rectNDC.RB.x, rectNDC.RB.y, 0.0f };

	list->at(0).color = _color;
	list->at(1).color = _color;
	list->at(2).color = _color;
	list->at(3).color = _color;

	m_pBorderShader->render();

	return false;
}

bool DXShaderBorderManager::initialize()
{
	m_pBorderShader = new DXShaderBorder;
	m_pBorderShader->setDevice(m_pd3dDevice, m_pImmediateContext);
	m_pBorderShader->setShaderFile(L"../include/core/HLSL/ShapeShader.txt");

	bool rst = m_pBorderShader->initialize();
	if (!rst)
	{
		OutputDebugString(L"WanyCore::DXShaderBorderManager::Failed Shader Initialize.\n");
		return false;
	}

	return true;
}

bool DXShaderBorderManager::frame()
{
	return true;
}

bool DXShaderBorderManager::render()
{
	return true;
}

bool DXShaderBorderManager::release()
{
	if (m_pBorderShader != nullptr)
	{
		m_pBorderShader->release();
		delete m_pBorderShader;
		m_pBorderShader = nullptr;
	}

	return true;
}
