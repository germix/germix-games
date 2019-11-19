////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBullet_Shotgun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/bullets/HeroBullet_Shotgun.h>
#include <src/ResourceManager.h>
#include <src/sprites/SpriteSheet.h>

#define BULLET_SHOTGUN_BASIC_LENGTH					150.0
#define BULLET_SHOTGUN_STRONG_LENGTH				200.0

#define BULLET_SHOTGUN_BASIC_VELOCITY				620.0
#define BULLET_SHOTGUN_STRONG_VELOCITY				700.0

#define BULLET_SHOTGUN_BASIC_DAMAGE_FOR_ENEMIES		15		// TODO Comprobrar valor de daños
#define BULLET_SHOTGUN_STRONG_DAMAGE_FOR_ENEMIES	25		// TODO Comprobrar valor de daños

#define BULLET_SHOTGUN_BASIC_DAMAGE_FOR_BULLETS		10
#define BULLET_SHOTGUN_STRONG_DAMAGE_FOR_BULLETS	15

HeroBullet_Shotgun::HeroBullet_Shotgun(Scene* s, double x, double y, double angle, int count, bool strong)
: HeroBullet(
			 s,
			 x,
			 y,
			 res.findSpriteSheet("bullets")->getSprite(
				!strong
					? ((count == 1) ? "hero.shotgun.basic1" : "hero.shotgun.basic2")
					: ((count == 1) ? "hero.shotgun.strong1" : "hero.shotgun.strong2")),
			 angle,
			 strong ? BULLET_SHOTGUN_STRONG_LENGTH : BULLET_SHOTGUN_BASIC_LENGTH,
			 strong ? BULLET_SHOTGUN_STRONG_VELOCITY : BULLET_SHOTGUN_BASIC_VELOCITY,
			 strong ? BULLET_SHOTGUN_STRONG_DAMAGE_FOR_ENEMIES : BULLET_SHOTGUN_BASIC_DAMAGE_FOR_ENEMIES,
			 strong ? BULLET_SHOTGUN_STRONG_DAMAGE_FOR_BULLETS : BULLET_SHOTGUN_BASIC_DAMAGE_FOR_BULLETS)
{
}
HeroBullet_Shotgun::~HeroBullet_Shotgun()
{
}
