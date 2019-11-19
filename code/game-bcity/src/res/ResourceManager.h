////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ResourceManager
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ResourceManager_h___
#define ___ResourceManager_h___
#include <src/res/ResourceList.h>

class Font;
class Sound;
class Music;
class Texture;

class ResourceManager
{
	ResourceList fontList;
	ResourceList soundList;
	ResourceList musicList;
	ResourceList textureList;
public:
	ResourceManager();
	~ResourceManager();
public:
	void load(const char* fname);
	Font* findFont(const char* name) const { return (Font*)fontList.get(name); }
	Sound* findSound(const char* name) const { return (Sound*)soundList.get(name); }
	Music* findMusic(const char* name) const { return (Music*)musicList.get(name); }
	Texture* findTexture(const char* name) const { return (Texture*)textureList.get(name); }
};

extern ResourceManager res;

#endif
