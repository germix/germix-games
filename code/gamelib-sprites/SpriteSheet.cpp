////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SpriteSheet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <gamelib-sprites/SpriteSheet.h>
#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteImage.h>
#include <gamelib-sprites/SpriteFrame.h>

#include <mach/Texture.h>

SpriteSheet::SpriteSheet()
{
}
SpriteSheet::~SpriteSheet()
{
	for(unsigned int i = 0; i < images.size(); i++)
		delete images[i];
	images.clear();
	for(unsigned int i = 0; i < sprites.size(); i++)
		delete sprites[i];
	sprites.clear();
	for(unsigned int i = 0; i < textures.size(); i++)
		delete textures[i];
	textures.clear();
}
Sprite* SpriteSheet::getSprite(const char* name) const
{
	for(unsigned int i = 0; i < sprites.size(); i++)
	{
		if(sprites[i]->name == name)
			return sprites[i];
	}
	return null;
}



