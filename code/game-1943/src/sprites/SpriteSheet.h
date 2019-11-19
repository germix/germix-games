////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SpriteSheet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SpriteSheet_h___
#define ___SpriteSheet_h___
#include <map>
#include <string>

class Sprite;

class SpriteSheet
{
	std::map<std::string,Sprite*> sprites;
public:
	SpriteSheet(const char* fname);
	~SpriteSheet();
public:
	Sprite* getSprite(const char* name) const;
};

#endif
