////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyWeapon_Simple
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/weapons/EnemyWeapon_Simple.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/enemies/bullets/EnemyBullet_Normal.H>

#include <mach/Math.h>

EnemyWeapon_Simple::EnemyWeapon_Simple()
{
}
EnemyWeapon_Simple::~EnemyWeapon_Simple()
{
}
void EnemyWeapon_Simple::shoot(Scene* scene, const Vector2f& p, double velocity)
{
	Hero* hero = scene->getHero();
	Vector2f heroPos = hero->position();
	double dx;
	double dy;
	double angle;
	dx = heroPos.x - p.x;
	dy = heroPos.y - p.y;
	angle = Math::atan2(dy, dx);
	scene->addEntity(new EnemyBullet_Normal(scene, p.x, p.y, angle, velocity));
}

