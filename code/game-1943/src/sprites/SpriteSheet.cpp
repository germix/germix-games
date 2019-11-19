////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SpriteSheet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/sprites/SpriteSheet.h>
#include <src/sprites/Sprite.h>

#include <tinyxml2/tinyxml2.h>

#include <mach/Texture.h>
#include <mach/TextureLoader.h>

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
	return p;
}

SpriteSheet::SpriteSheet(const char* fname)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* root;
	tinyxml2::XMLElement* elem;
	
	if(tinyxml2::XML_SUCCESS != doc.LoadFile(fname))
		return;
	
	char  path[256];
	char* p = getPath(fname, path);

	if(null != (root = doc.FirstChildElement("SpriteSheet")))
	{
		for(elem = root->FirstChildElement("Sprite"); elem != null; elem = elem->NextSiblingElement())
		{
			const char* s;
			std::string name;
			Sprite* sprite = new Sprite();
			
			elem->QueryStringAttribute("name", &s);
			name = s;
			
			elem->QueryStringAttribute("count", &s);
			sprite->count = atoi(s);
			
			elem->QueryStringAttribute("image", &s);
			strcpy(p, s);
			sprite->texture = TextureLoader::load(path);
			sprite->width = sprite->texture->getWidth()/sprite->count;
			sprite->height = sprite->texture->getHeight();

			sprites[name] = sprite;
		}
	}
}
SpriteSheet::~SpriteSheet()
{
	for(std::map<std::string,Sprite*>::const_iterator it = sprites.begin(); it != sprites.end(); it++)
	{
		delete it->second;
	}
	sprites.clear();
}
Sprite* SpriteSheet::getSprite(const char* name) const
{
	for(std::map<std::string,Sprite*>::const_iterator it = sprites.begin(); it != sprites.end(); it++)
	{
		if(it->first == name)
			return it->second;
	}
	return null;
}

