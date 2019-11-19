////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyBullet_Normal
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/bullets/EnemyBullet_Normal.h>
#include <src/ResourceManager.h>
#include <src/sprites/SpriteSheet.h>

EnemyBullet_Normal::EnemyBullet_Normal(Scene* s, double x, double y, double angle, double velocity)
: EnemyBullet(
			  s,
			  x,
			  y,
			  res.findSpriteSheet("bullets")->getSprite("enemy.normal"),
			  angle,
			  velocity,
			  10)
{
}
EnemyBullet_Normal::~EnemyBullet_Normal()
{
}
