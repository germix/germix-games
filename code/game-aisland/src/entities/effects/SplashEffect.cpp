////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SplashEffect
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/effects/SplashEffect.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

SplashEffect::SplashEffect(Scene* s, double x, double y) : Entity(s, x, y)
, sheet(res.findSpriteSheet("Splash"))
, sprite(sheet->getSprite("Idle"))
, spriteIndex(0)
, spriteClock(0.04)
{
}
SplashEffect::~SplashEffect()
{
}
void SplashEffect::update(double dt)
{
	if(spriteClock.update(dt))
	{
		spriteIndex++;
		if(spriteIndex >= sprite->count())
			removable = true;
	}
}
void SplashEffect::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteIndex, 0);
}

