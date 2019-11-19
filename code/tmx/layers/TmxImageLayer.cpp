////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TmxImageLayer
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <tmx/layers/TmxImageLayer.h>

#include "../utils.h"
#include <tinyxml2/tinyxml2.h>

TmxImageLayer::TmxImageLayer(tinyxml2::XMLElement* elem)
{
	const char* s;
	
	readProperties(properties, elem);
	
	elem->QueryStringAttribute("name", &s);
	name = s;
	
	elem->QueryIntAttribute("width", &width);
	
	elem->QueryIntAttribute("height", &height);
	
	if(null != (elem = elem->FirstChildElement("image")))
	{
		elem->QueryStringAttribute("source", &s);
		image = s;
	}
}
TmxImageLayer::~TmxImageLayer()
{
}
