#pragma once
#include "DXShader.hpp"

class DXShaderBorder : public DXShader
{
private:
	virtual void initializeIndexList() override;

public:
	virtual bool render() override;
};