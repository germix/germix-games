////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyBullet_Missile
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/bullets/EnemyBullet_Missile.h>
#include <src/ResourceManager.h>
#include <src/sprites/SpriteSheet.h>
#include <src/Utils.h>

EnemyBullet_Missile::EnemyBullet_Missile(Scene* s, double x, double y, double angle, double velocity, bool big)
: EnemyBullet(
			  s,
			  x,
			  y,
			  res.findSpriteSheet("bullets")->getSprite(big ? "enemy.missile.big" : "enemy.missile.1"),
			  angle,
			  velocity,
			  20)
{
}
EnemyBullet_Missile::~EnemyBullet_Missile()
{
}
void EnemyBullet_Missile::update(double dt)
{
	EnemyBullet::update(dt);
	frame = Utils::spriteFromAngle(angle, 16);
}
