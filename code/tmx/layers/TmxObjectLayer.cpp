////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TmxObjectLayer
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <tmx/layers/TmxObjectLayer.h>
#include <tmx/TmxObject.h>

#include "../utils.h"
#include <tinyxml2/tinyxml2.h>

TmxObjectLayer::TmxObjectLayer(tinyxml2::XMLElement* elem)
{
	const char* s;
	
	readProperties(properties, elem);
	
	elem->QueryStringAttribute("name", &s);
	name = s;
	
	elem->QueryIntAttribute("width", &width);
	elem->QueryIntAttribute("height", &height);
	
	for(elem = elem->FirstChildElement("object"); elem != null; elem = elem->NextSiblingElement())
	{
		objects.push_back(new TmxObject(elem));
	}
}
TmxObjectLayer::~TmxObjectLayer()
{
	for(unsigned int i = 0; i < objects.size(); i++)
		delete objects[i];
	objects.clear();
}
