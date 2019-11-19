////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBullet_Shell
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/bullets/HeroBullet_Shell.h>
#include <src/ResourceManager.h>
#include <src/sprites/SpriteSheet.h>

#define BULLET_SHELL_LENGTH						(-1)
#define BULLET_SHELL_VELOCITY					570.0
#define BULLET_SHELL_DAMAGE_FOR_ENEMIES			16		// TODO Comprobrar valor de daños
#define BULLET_SHELL_DAMAGE_FOR_BULLETS			0


HeroBullet_Shell::HeroBullet_Shell(Scene* s, double x, double y, double angle)
: HeroBullet(
			 s,
			 x,
			 y,
			 res.findSpriteSheet("bullets")->getSprite("hero.shell"),
			 angle,
			 BULLET_SHELL_LENGTH,
			 BULLET_SHELL_VELOCITY,
			 BULLET_SHELL_DAMAGE_FOR_ENEMIES,
			 BULLET_SHELL_DAMAGE_FOR_BULLETS)
{
}
HeroBullet_Shell::~HeroBullet_Shell()
{
}
