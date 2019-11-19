////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyWeapon_Missile
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/weapons/EnemyWeapon_Missile.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/enemies/bullets/EnemyBullet_Missile.h>

#include <mach/Math.h>

EnemyWeapon_Missile::EnemyWeapon_Missile()
{
}
EnemyWeapon_Missile::~EnemyWeapon_Missile()
{
}
void EnemyWeapon_Missile::shoot(Scene* scene, const Vector2f& p, double velocity)
{
	Hero* hero = scene->getHero();
	Vector2f heroPos = hero->position();
	double dx;
	double dy;
	double angle;
	dx = heroPos.x - p.x;
	dy = heroPos.y - p.y;
	angle = Math::atan2(dy, dx);
	scene->addEntity(new EnemyBullet_Missile(scene, p.x, p.y, angle, velocity, false));
}
