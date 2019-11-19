////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBullet_Normal
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/bullets/HeroBullet_Normal.h>
#include <src/ResourceManager.h>
#include <src/sprites/SpriteSheet.h>

#define BULLET_NORMAL_LENGTH					(-1)
#define BULLET_NORMAL_VELOCITY					500.0
#define BULLET_NORMAL_DAMAGE_FOR_ENEMIES		10			// TODO Comprobrar valor de daños
#define BULLET_NORMAL_DAMAGE_FOR_BULLETS		0

HeroBullet_Normal::HeroBullet_Normal(Scene* s, double x, double y, double angle)
: HeroBullet(
			 s,
			 x,
			 y,
			 res.findSpriteSheet("bullets")->getSprite("hero.normal"),
			 angle,
			 BULLET_NORMAL_LENGTH,
			 BULLET_NORMAL_VELOCITY,
			 BULLET_NORMAL_DAMAGE_FOR_ENEMIES,
			 BULLET_NORMAL_DAMAGE_FOR_BULLETS)
{
}
HeroBullet_Normal::~HeroBullet_Normal()
{
}

