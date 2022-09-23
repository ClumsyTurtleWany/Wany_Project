#include "DXShaderBorderManager.hpp"

void DXShaderBorderManager::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}

void DXShaderBorderManager::setCamera(Camera* _camera)
{
	renderCamera = _camera;
}

void DXShaderBorderManager::setMapSize(Vector2f _size)
{
	mapSize = _size;
}

bool DXShaderBorderManager::drawBorder(const Rect2f& _rect, const Vector4f& _color)
{
	if (renderCamera == nullptr)
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
	}
	else
	{
		float mapWidth_Half = mapSize.x * 0.5f;
		float mapHeight_Half = mapSize.y * 0.5f;

		Rect_<float> rectOrthogonal;
		rectOrthogonal.LT.x = _rect.LT.x - mapWidth_Half;
		rectOrthogonal.LT.y = mapHeight_Half - _rect.LT.y;
		rectOrthogonal.RB.x = _rect.RB.x - mapWidth_Half;
		rectOrthogonal.RB.y = mapHeight_Half - _rect.RB.y;

		Rect_<float> rectCameraTemp = renderCamera->getRect();
		Rect_<float> rectCamera;
		rectCamera.LT.x = rectCameraTemp.LT.x - mapWidth_Half;
		rectCamera.LT.y = mapHeight_Half - rectCameraTemp.LT.y;
		rectCamera.RB.x = rectCameraTemp.RB.x - mapWidth_Half;
		rectCamera.RB.y = mapHeight_Half - rectCameraTemp.RB.y;

		Rect_<float> rectView;
		rectView.LT.x = (rectOrthogonal.LT.x - rectCamera.LT.x);
		rectView.LT.y = (rectOrthogonal.LT.y - rectCamera.LT.y);
		rectView.RB.x = (rectOrthogonal.RB.x - rectCamera.LT.x);
		rectView.RB.y = (rectOrthogonal.RB.y - rectCamera.LT.y);

		float width = rectCamera.RB.x - rectCamera.LT.x;
		float height = rectCamera.LT.y - rectCamera.RB.y;
		float width_half = width * 0.5f;
		float height_half = height * 0.5f;

		Rect_<float> rectNDC;
		rectNDC.LT.x = (rectView.LT.x - width_half) / width_half;
		rectNDC.LT.y = (rectView.LT.y + height_half) / height_half;
		rectNDC.RB.x = (rectView.RB.x - width_half) / width_half;
		rectNDC.RB.y = (rectView.RB.y + height_half) / height_half;

		std::vector<Vertex>* list = m_pBorderShader->getVertexList();
		list->at(0).pos = { rectNDC.LT.x, rectNDC.LT.y, 0.0f };
		list->at(1).pos = { rectNDC.RB.x, rectNDC.LT.y, 0.0f };
		list->at(2).pos = { rectNDC.LT.x, rectNDC.RB.y, 0.0f };
		list->at(3).pos = { rectNDC.RB.x, rectNDC.RB.y, 0.0f };

		list->at(0).color = _color;
		list->at(1).color = _color;
		list->at(2).color = _color;
		list->at(3).color = _color;
	}

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
