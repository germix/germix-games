////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBullet_Auto
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/bullets/HeroBullet_Auto.h>
#include <src/ResourceManager.h>
#include <src/sprites/SpriteSheet.h>

#define BULLET_AUTO_LENGTH						(-1)
#define BULLET_AUTO_VELOCITY					580.0
#define BULLET_AUTO_DAMAGE_FOR_ENEMIES			18			// TODO Comprobrar valor de daños
#define BULLET_AUTO_DAMAGE_FOR_BULLETS			0

HeroBullet_Auto::HeroBullet_Auto(Scene* s, double x, double y, double angle)
: HeroBullet(
			 s,
			 x,
			 y,
			 res.findSpriteSheet("bullets")->getSprite("hero.auto"),
			 angle,
			 BULLET_AUTO_LENGTH,
			 BULLET_AUTO_VELOCITY,
			 BULLET_AUTO_DAMAGE_FOR_ENEMIES,
			 BULLET_AUTO_DAMAGE_FOR_BULLETS)
{
}
HeroBullet_Auto::~HeroBullet_Auto()
{
}
