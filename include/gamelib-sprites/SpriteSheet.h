////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SpriteSheet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SpriteSheet_h___
#define ___SpriteSheet_h___
#include <vector>

class Texture;
class Sprite;
class SpriteFrame;
class SpriteImage;

class SpriteSheet
{
public:
	std::vector<SpriteImage*>	images;
	std::vector<Sprite*>		sprites;
	std::vector<Texture*>		textures;
public:
	SpriteSheet();
	~SpriteSheet();
public:
	Sprite* getSprite(const char* name = "") const;
};

#endif
