////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TmxMap
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <tmx/TmxMap.h>
#include <tmx/layers/TmxImageLayer.h>
#include <tmx/layers/TmxObjectLayer.h>
#include <tmx/layers/TmxPatternLayer.h>
#include <tmx/layers/TmxTilesetLayer.h>

#include "utils.h"
#include <tinyxml2/tinyxml2.h>

using namespace tinyxml2;

TmxMap::TmxMap(const char* fileName)
	: orientation(ORIENTATION_UNKNOWN)
	, mapWidth(0)
	, mapHeight(0)
	, tileWidth(0)
	, tileHeight(0)
{
	const char* s;
	XMLError err;
	XMLDocument doc;
	XMLElement* root;
	XMLElement* elem;
	
	err = doc.LoadFile(fileName);
	if(err != XML_SUCCESS)
		return;
	
	root = doc.FirstChildElement("map");
	
	//
	// Orientación
	//
	root->QueryStringAttribute("orientation", &s);
	if(0 == strcmp(s, "isometric"))
		orientation = ORIENTATION_ISOMETRIC;
	else if(0 == strcmp(s, "orthogonal"))
		orientation = ORIENTATION_ORTHOGONAL;
	
	//
	// Dimensiones
	//
	root->QueryIntAttribute("width", &mapWidth);
	root->QueryIntAttribute("height", &mapHeight);
	root->QueryIntAttribute("tilewidth", &tileWidth);
	root->QueryIntAttribute("tileheight", &tileHeight);
	
	//
	// Leer propiedades
	//
	readProperties(properties, root);

	//
	// Leer capas del mapa
	//
	for(elem = root->FirstChildElement("imagelayer"); elem != null; elem = elem->NextSiblingElement())
	{
		imageLayers.push_back(new TmxImageLayer(elem));
	}
	for(elem = root->FirstChildElement("objectgroup"); elem != null; elem = elem->NextSiblingElement())
	{
		objectLayers.push_back(new TmxObjectLayer(elem));
	}
	for(elem = root->FirstChildElement("layer"); elem != null; elem = elem->NextSiblingElement())
	{
		patternLayers.push_back(new TmxPatternLayer(elem));
	}
	for(elem = root->FirstChildElement("tileset"); elem != null; elem = elem->NextSiblingElement())
	{
		tilesetLayers.push_back(new TmxTilesetLayer(elem));
	}
}
TmxMap::~TmxMap()
{
	for(unsigned int i = 0; i < imageLayers.size(); i++) delete imageLayers[i];
	for(unsigned int i = 0; i < objectLayers.size(); i++) delete objectLayers[i];
	for(unsigned int i = 0; i < patternLayers.size(); i++) delete patternLayers[i];
	for(unsigned int i = 0; i < tilesetLayers.size(); i++) delete tilesetLayers[i];
	
	imageLayers.clear();
	objectLayers.clear();
	patternLayers.clear();
	tilesetLayers.clear();
}
const char* TmxMap::getOrientationName() const
{
	switch(orientation)
	{
		case ORIENTATION_ISOMETRIC:
			return "Isometric";
		case ORIENTATION_ORTHOGONAL:
			return "Orthogonal";
	}
	return "Unknown";
}
const TmxImageLayer* TmxMap::getImageLayer(const char* layerName) const
{
	for(unsigned int i = 0; i < imageLayers.size(); i++)
	{
		if(imageLayers[i]->getName() == layerName)
			return imageLayers[i];
	}
	return null;
}
const TmxObjectLayer* TmxMap::getObjectLayer(const char* layerName) const
{
	for(unsigned int i = 0; i < objectLayers.size(); i++)
	{
		if(objectLayers[i]->getName() == layerName)
			return objectLayers[i];
	}
	return null;
}
const TmxPatternLayer* TmxMap::getPatternLayer(const char* layerName) const
{
	for(unsigned int i = 0; i < patternLayers.size(); i++)
	{
		if(patternLayers[i]->getName() == layerName)
			return patternLayers[i];
	}
	return null;
}
const TmxTilesetLayer* TmxMap::getTilesetLayer(const char* layerName) const
{
	for(unsigned int i = 0; i < tilesetLayers.size(); i++)
	{
		if(tilesetLayers[i]->getName() == layerName)
			return tilesetLayers[i];
	}
	return null;
}
