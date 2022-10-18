#include "Object.hpp"


bool objectBase::initialize()
{
	return pShader->initialize();
}

bool objectBase::frame()
{
	return true;
}

bool objectBase::render()
{
	return pShader->render();
}

bool objectBase::release()
{
	if (DXShaderManager::getInstance()->DeleteShader(object_id))
	{
		return true;
	}
	return false;
}

void objectBase::updateShader()
{
}

void objectBase::updateShaderCamera()
{
}

void objectBase::setDevice(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	pShader->setDevice(_device, _context);
}

bool objectBase::createShader(ShaderType _type)
{
	if (DXShaderManager::getInstance()->Load(object_id, _type))
	{
		pShader = DXShaderManager::getInstance()->getShader(object_id);
		return true;
	}
	return false;
}


void objectBase::setTexture(DXTexture* _texture)
{
	pShader->setTexture(_texture);
}

void objectBase::setTextureMask(DXTexture* _mask)
{
	pShader->setTextureMask(_mask);
}

void objectBase::setColor(Vector4f _color)
{
	pShader->setColor(_color);	
}

void objectBase::setSpriteList(const std::vector<Rect_<float>>& _list)
{
	if (!_list.empty())
	{
		SpriteList.clear();
		SpriteList.assign(_list.begin(), _list.end());
	}
}