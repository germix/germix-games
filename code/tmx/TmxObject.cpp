////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TmxObject
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <tmx/TmxObject.h>

#include "utils.h"
#include <tinyxml2/tinyxml2.h>

TmxObject::TmxObject(tinyxml2::XMLElement* elem)
{
	const char* s;
	
	readProperties(properties, elem);
	
	elem->QueryStringAttribute("type", &s);
	type = s;
	
	elem->QueryIntAttribute("x", &x);
	elem->QueryIntAttribute("y", &y);
	elem->QueryIntAttribute("width", &width);
	elem->QueryIntAttribute("height", &height);

	elem->QueryBoolAttribute("visible", &visible);

	//
	// Leer point, o ancho y largo
	//
	if(null != (elem = elem->FirstChildElement("polyline")))
	{
		width = 0;
		height = 0;
		elem->QueryStringAttribute("points", &s);
		polyline = s;
	}
}
TmxObject::~TmxObject()
{
}
