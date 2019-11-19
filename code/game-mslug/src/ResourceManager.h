////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ResourceManager
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ResourceManager_h___
#define ___ResourceManager_h___
#include <src/ResourceList.h>

class Font;
class Sound;
class Music;
class Texture;
class SpriteSheet;

class ResourceManager
{
	ResourceList fontList;
	ResourceList soundList;
	ResourceList musicList;
	ResourceList textureList;
	ResourceList spriteSheetList;
public:
	ResourceManager();
	~ResourceManager();
public:
	void load(const char* fname);
	Font* findFont(const char* name) const { return (Font*)fontList.get(name); }
	Sound* findSound(const char* name) const { return (Sound*)soundList.get(name); }
	Music* findMusic(const char* name) const { return (Music*)musicList.get(name); }
	Texture* findTexture(const char* name) const { return (Texture*)textureList.get(name); }
	SpriteSheet* findSpriteSheet(const char* name) const { return (SpriteSheet*)spriteSheetList.get(name); }
};

extern ResourceManager res;

#endif