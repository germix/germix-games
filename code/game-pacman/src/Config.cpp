////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Config
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Config.h>
#include <src/resources/ResourceManager.h>

const bool Debug::collisionMap = false;		// default=false
const bool Debug::ghostDir = false;			// default=false
const bool Debug::ghostPath = false;		// default=false
const bool Debug::pacmanLives = true;		// default=true
const bool Debug::pacmanDamaged = true;		// default=true

const bool Debug::noCollisionWithGhosts = false;

int Config::maxScore = 0;
Texture* Config::currentTileset = null;
std::string Config::currentTilesetName = "";

#include <tinyxml2/tinyxml2.h>

using namespace tinyxml2;

void Config::load()
{
	XMLDocument doc;
	XMLElement* root;
	const char* attr;
	
	if(XML_SUCCESS == doc.LoadFile("pacman.config"))
	{
		if(null != (root = doc.FirstChildElement("Pacman")))
		{
			root->QueryIntAttribute("maxscore", &maxScore);
			
			root->QueryStringAttribute("tileset", &attr);
			currentTileset = res.findTexture(attr);
			currentTilesetName = attr;
		}
	}
	if(!currentTileset)
	{
		currentTileset = res.findTexture((currentTilesetName = "classic-blue").c_str());
	}
}
void Config::save()
{
	XMLDocument doc;
	XMLElement* root;
	
	root = doc.NewElement("Pacman");
	root->SetAttribute("maxscore", maxScore);
	root->SetAttribute("tileset", currentTilesetName.c_str());
	doc.InsertFirstChild(root);
	
	doc.SaveFile("pacman.config");
}

