#include "Scene.hpp"

Scene::Scene(MapleStory* _game) : game(_game)
{
}

Scene::~Scene()
{
}

void Scene::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	m_pd3dDevice = _device;
	m_pImmediateContext = _context;
}