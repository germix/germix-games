////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBullet_3way
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/bullets/HeroBullet_3way.h>
#include <src/ResourceManager.h>
#include <src/sprites/SpriteSheet.h>

#define BULLET_3WAY_LENGTH						(-1)
#define BULLET_3WAY_VELOCITY					500.0
#define BULLET_3WAY_DAMAGE_FOR_ENEMIES			10			// TODO Comprobrar valor de daños
#define BULLET_3WAY_DAMAGE_FOR_BULLETS			0

HeroBullet_3way::HeroBullet_3way(Scene* s, double x, double y, double angle, int dir)
: HeroBullet(
			 s,
			 x,
			 y,
			 res.findSpriteSheet("bullets")->getSprite((dir == -1) ? "hero.3way.left" : ((dir == +1) ? "hero.3way.right" : "hero.3way")),
			 angle,
			 BULLET_3WAY_LENGTH,
			 BULLET_3WAY_VELOCITY,
			 BULLET_3WAY_DAMAGE_FOR_ENEMIES,
			 BULLET_3WAY_DAMAGE_FOR_BULLETS)

{
}
HeroBullet_3way::~HeroBullet_3way()
{
}

