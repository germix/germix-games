////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Mission
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Mission.h>
#include <src/scene/Scene.h>
#include <src/scene/MissionMap.h>
#include <src/scene/MissionMapRenderable.h>

#include <tinyxml2/tinyxml2.h>

#include <mach/Mixer.h>
#include <mach/ImageLoader.h>
#include <mach/TextureLoader.h>

using namespace tinyxml2;

static char* getPath(const char* fname, char* path)
{
	char* p;
	
	p = (char*)strrchr(fname, '/');
	if(p == null)
		p = (char*)strrchr(fname, '\\');
	if(p == null)
	{
		p = path;
	}
	else
	{
		char* dst = path;
		const char* src = fname;
		while(src <= p)
		{
			*dst++ = *src++;
		}
		p = dst;
	}
	*p = 0;
	return p;
}

Mission::Mission()
{
}
Mission::~Mission()
{
}
Map* Mission::load(const char* fname)
{
	XMLError err;
	XMLDocument doc;
	XMLElement* root;
	XMLElement* elem;
	
	err = doc.LoadFile(fname);
	if(err != XML_SUCCESS)
		return null;
	
	if(null != (root = doc.FirstChildElement("Scene")))
	{
		MissionMap* map = new MissionMap();
		char  path[256];
		char* semiPath = getPath(fname, path);
		
		if(null != (elem = root->FirstChildElement("Map")))
		{
			readMap(map, path, semiPath, elem);
		}
		if(null != (elem = root->FirstChildElement("Music")))
		{
			readMusic(map, path, semiPath, elem);
		}
		if(null != (elem = root->FirstChildElement("Entities")))
		{
			readEntities(map, path, semiPath, elem);
		}
		if(null != (elem = root->FirstChildElement("Backgrounds")))
		{
			readRenderables(map, path, semiPath, elem, "Background", map->backgrounds);
		}
		if(null != (elem = root->FirstChildElement("Foregrounds")))
		{
			readRenderables(map, path, semiPath, elem, "Foreground", map->foregrounds);
		}
		return map;
	}
	return null;
}
void Mission::readMap(MissionMap* map, const char* fullPath, char* semiPath, tinyxml2::XMLElement* elem)
{
	const char* value;
	Image* slopesTerrain;

	elem->QueryStringAttribute("platform", &value);
	
	strcpy(semiPath, value);
	map->terrain = ImageLoader::load(fullPath);
	map->width = map->terrain->getWidth();
	map->height = map->terrain->getHeight();
	
	elem->QueryStringAttribute("offsets", &value);
	strcpy(semiPath, value);
	if(null != (slopesTerrain = ImageLoader::load(fullPath)))
	{
		int x;
		int y;
		int width = slopesTerrain->getWidth();
		int height = slopesTerrain->getHeight();
		
		map->slopes = new int[width];
		for(x = 0; x < width; x++)
		{
			for(y = height-1; y >= 0; y--)
			{
				if(slopesTerrain->getColor(x, y).alpha() == 0)
				{
					break;
				}
			}
			map->slopes[x] = y+1;
		}
		delete slopesTerrain;
	}
	elem->QueryStringAttribute("backgroundColor", &value);
	map->backgroundColor = Color(value);
}
void Mission::readMusic(MissionMap* map, const char* fullPath, char* semiPath, tinyxml2::XMLElement* elem)
{
	const char* value;
	
	elem->QueryStringAttribute("music", &value);
	strcpy(semiPath, value);
	map->missionMusic = Mixer::loadMusic(fullPath);
}
void Mission::readEntities(MissionMap* map, const char* fullPath, char* semiPath, tinyxml2::XMLElement* elem)
{
	for(elem = elem->FirstChildElement("Entity"); elem != null; elem = elem->NextSiblingElement())
	{
		const char* value;
		MissionMap::EntitySpawnNode* node;
		
		elem->QueryStringAttribute("class", &value);
		node = new MissionMap::EntitySpawnNode(value);
		
		elem->QueryStringAttribute("x", &value);
		node->x = atoi(value);
		elem->QueryStringAttribute("y", &value);
		node->y = atoi(value);
		
		if(0 == elem->QueryStringAttribute("boss", &value))
			node->boss = true;
		else
			node->boss = false;
		
		node->prev = null;
		node->next = null;

		XMLElement* argsElem;
		if(null != (argsElem = elem->FirstChildElement("Arguments")))
		{
			for(const XMLAttribute* attr = argsElem->FirstAttribute(); attr != null; attr = attr->Next())
			{
				node->params.map[attr->Name()] = attr->Value();
			}
		}
		
		if(map->entitySpawner.head == null)
		{
			map->entitySpawner.head = node;
			map->entitySpawner.tail = node;
		}
		else
		{
			node->prev = map->entitySpawner.tail;
			map->entitySpawner.tail->next = node;
			map->entitySpawner.tail = node;
		}
	}
}
void Mission::readRenderables(MissionMap* map, const char* fullPath, char* semiPath, tinyxml2::XMLElement* elem, const char* elemName, std::vector<MissionMapRenderable*>& renderables)
{
	for(elem = elem->FirstChildElement(elemName); elem != null; elem = elem->NextSiblingElement())
	{
		XMLElement* imageElem = elem->FirstChildElement("Image");
		if(imageElem)
		{
			int x;
			int y;
			int w = 0;
			int h = 0;
			MissionMapRenderable* r = new MissionMapRenderable();
			std::string type;
			const char* value;
			
			elem->QueryIntAttribute("x", &x);
			elem->QueryIntAttribute("y", &y);
			elem->QueryIntAttribute("width", &w);
			elem->QueryIntAttribute("height", &h);
			elem->QueryStringAttribute("type", &value);
			
			r->type = (strcmp(value, "parallax") == 0) ? MissionMapRenderable::TYPE_PARALLAX : MissionMapRenderable::TYPE_FIXED;
			
			for(; imageElem != null; imageElem = imageElem->NextSiblingElement())
			{
				imageElem->QueryStringAttribute("image", &value);
				
				strcpy(semiPath, value);
				r->textures.push_back(TextureLoader::load(fullPath));
			}
			if(w == 0)
				w = r->textures[0]->getWidth();
			if(h == 0)
				h = r->textures[0]->getHeight();
			
			r->rect = Rectangle(x, y, w, h);
			
			renderables.push_back(r);
		}
	}
}
