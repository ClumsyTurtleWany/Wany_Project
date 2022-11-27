#include "DaeFile.h"

bool DaeFile::Load(std::string filename)
{
	TiXmlDocument doc;
	if (!doc.LoadFile(filename.c_str()))
	{
		return false;
	}

	// Root Node
	TiXmlElement* root = doc.FirstChildElement();

	// Asset Information
	TiXmlElement* asset = root->FirstChildElement("asset");
	TiXmlElement* upAxis = asset->FirstChildElement("up_axis");	
	std::string axisVal = upAxis->GetText();

	// Library images == Texture images
	TiXmlElement* images = root->FirstChildElement("library_images");
	TiXmlElement* image = images->FirstChildElement("image");
	for (TiXmlElement* target = image; target != nullptr; target = target->NextSiblingElement())
	{
		TiXmlAttribute* attribute = target->FirstAttribute();
		std::string name = attribute->Name();
		std::string id = attribute->Value();

		TiXmlElement* ele = target->FirstChildElement("init_from")->FirstChildElement("ref");
		std::string textureName = ele->GetText();
	}

	// Library effects
	TiXmlElement* effects = root->FirstChildElement("library_effects");
	TiXmlElement* effect = effects->FirstChildElement("effect");
	for (TiXmlElement* target = effect; target != nullptr; target = target->NextSiblingElement())
	{
		TiXmlAttribute* attribute = target->FirstAttribute();
		std::string name = attribute->Name();
		std::string id = attribute->Value();

		TiXmlElement* profile = target->FirstChildElement("profile_COMMON");
		TiXmlElement* technique = profile->FirstChildElement("technique");
		if (technique != nullptr)
		{
			attribute = technique->FirstAttribute();
			std::string id = attribute->Value();

			TiXmlElement* blinn = technique->FirstChildElement("blinn");
			TiXmlElement* diffuse = blinn->FirstChildElement("diffuse")->FirstChildElement("color");
			std::string val = diffuse->GetText();
		}
		
		TiXmlElement* newparam = profile->FirstChildElement("newparam");
		if (newparam != nullptr)
		{

		}
	}

	return false;
}
