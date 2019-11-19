////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TmxTilesetLayer
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <tmx/layers/TmxTilesetLayer.h>

#include "../utils.h"
#include <tinyxml2/tinyxml2.h>

TmxTilesetLayer::TmxTilesetLayer(tinyxml2::XMLElement* elem)
{
	const char* s;
	
	readProperties(properties, elem);
	
	elem->QueryStringAttribute("name", &s);
	name = s;
	
	elem->QueryIntAttribute("firstgid", &firstgid);
	elem->QueryIntAttribute("tilewidth", &tileWidth);
	elem->QueryIntAttribute("tileheight", &tileHeight);

	if(null != (elem = elem->FirstChildElement("image")))
	{
		elem->QueryStringAttribute("source", &s);
		imageName = s;
		
		elem->QueryIntAttribute("width", &imageWidth);
		elem->QueryIntAttribute("height", &imageHeight);
	}
}
TmxTilesetLayer::~TmxTilesetLayer()
{
}
