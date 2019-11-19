////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ResourceManager
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/ResourceManager.h>

#include <string.h>
#include <tinyxml2/tinyxml2.h>

#include <mach/Mixer.h>
#include <mach/TextureLoader.h>
#include <gamelib/FontLoader.h>
#include <src/sprites/SpriteSheet.h>

using namespace tinyxml2;

#if 0
class ResourceFile
{
public:
	unsigned int	ref;
};
#endif

ResourceManager res;

static int toType(const char* type)
{
	if(0 == strcmp(type, "Font"))			return RESOURCE_TYPE_FONT;
	if(0 == strcmp(type, "Sound"))			return RESOURCE_TYPE_SOUND;
	if(0 == strcmp(type, "Music"))			return RESOURCE_TYPE_MUSIC;
	if(0 == strcmp(type, "Texture"))		return RESOURCE_TYPE_TEXTURE;
	if(0 == strcmp(type, "SpriteSheet"))	return RESOURCE_TYPE_SPRITESHEET;
	return -1;
}
ResourceManager::ResourceManager()
{
}
ResourceManager::~ResourceManager()
{
}
void ResourceManager::load(const char* fname)
{
	XMLError err;
	XMLDocument doc;
	XMLElement* elem;
	const char* value;
	
	err = doc.LoadFile(fname);
	if(err != XML_SUCCESS)
		return;
	
	char* p;
	char  path[256];
	
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
	if(null != (elem = doc.FirstChildElement("Resources")))
	{
		for(elem = elem->FirstChildElement("Resource"); elem != null; elem = elem->NextSiblingElement())
		{
			int type;
			void* handle = 0;
			
			// Tipo
			elem->QueryStringAttribute("type", &value);
			type = toType(value);
			
			if(type != -1)
			{
				// Recurso
				elem->QueryStringAttribute("file", &value);
				strcpy(p, value);
				switch(type)
				{
					case RESOURCE_TYPE_FONT:		handle = FontLoader::load(path);		break;
					case RESOURCE_TYPE_SOUND:		handle = Mixer::loadSound(path);		break;
					case RESOURCE_TYPE_MUSIC:		handle = Mixer::loadMusic(path);		break;
					case RESOURCE_TYPE_TEXTURE:		handle = TextureLoader::load(path);		break;
					case RESOURCE_TYPE_SPRITESHEET:	handle = new SpriteSheet(path);			break;
				}
				if(!handle)
				{
					printf("Can't found resource file \"%s\"\n", path);
				}
				else
				{
					// Nombre
					elem->QueryStringAttribute("name", &value);

					// Insertar
					switch(type)
					{
						case RESOURCE_TYPE_FONT:		fontList.insert(value, handle, type);			break;
						case RESOURCE_TYPE_SOUND:		soundList.insert(value, handle, type);			break;
						case RESOURCE_TYPE_MUSIC:		musicList.insert(value, handle, type);			break;
						case RESOURCE_TYPE_TEXTURE:		textureList.insert(value, handle, type);		break;
						case RESOURCE_TYPE_SPRITESHEET:	spriteSheetList.insert(value, handle, type);	break;
					}
				}
			}
		}
	}
}

