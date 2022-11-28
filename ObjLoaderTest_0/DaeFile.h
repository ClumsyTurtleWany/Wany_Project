#pragma once
#include <fstream>
#include <sstream>

#include "Define.hpp"
#include "tinystr.h"
#include "tinyxml.h"

class DaeFile
{
public:
	// Asset Infomation
	// _axis[0]: front
	// _axis[1]: right
	// _axis[2]: up
	std::string _axis[3];

	// Texture Images name
	std::map<std::string, std::string> _textureImages;

public:
	bool Load(std::string filename);

public:
	//----------------------------------------
	// Common Function
	//----------------------------------------
	bool SplitString(std::string line, char delimiter, std::vector<std::string>& dst);

public:
	//----------------------------------------
	// Parser Function
	//----------------------------------------

	// Asset Infomation
	bool ParseAssetInfo(TiXmlElement* parent);

	// Texture images name
	bool ParseLibImages(TiXmlElement* parent);

	// Texture process method
	bool ParseLibEffects(TiXmlElement* parent);

	// Material
	bool ParseLidbMaterials(TiXmlElement* parent);

	// Geometries -> Geometry
	bool ParseLibGeometries(TiXmlElement* parent);
	bool ParseGeometryMesh(TiXmlElement* parent, std::string id);
	bool ParseGeometryMeshSource(TiXmlElement* parent);
	bool ParseGeometryMeshVertices(TiXmlElement* parent);
	bool ParseGeometryMeshTriangles(TiXmlElement* parent);
};