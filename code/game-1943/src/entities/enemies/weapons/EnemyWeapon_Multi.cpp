////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyWeapon_Multi
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/weapons/EnemyWeapon_Multi.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/enemies/bullets/EnemyBullet_Normal.h>

#include <mach/Math.h>

EnemyWeapon_Multi::EnemyWeapon_Multi()
{
}
EnemyWeapon_Multi::~EnemyWeapon_Multi()
{
}
void EnemyWeapon_Multi::shoot(Scene* scene, const Vector2f& p, double velocity)
{
	Hero* hero = scene->getHero();
	Vector2f heroPos = hero->position();
	double dx;
	double dy;
	double angle;
	double degrees;
	if(heroPos.y < p.y)
	{
		dy = 0;
	}
	else
	{
		dy = heroPos.y - p.y;
	}
	dx = heroPos.x - p.x;
	angle = Math::atan2(dy, dx);
	degrees = Math::toDegrees(angle);
	double di1 = degrees - 30;
	double di2 = degrees - 65;
	double dr1 = degrees + 30;
	double dr2 = degrees + 65;
	scene->addEntity(new EnemyBullet_Normal(scene, p.x, p.y, Math::toRadians(degrees), velocity));
	scene->addEntity(new EnemyBullet_Normal(scene, p.x, p.y, Math::toRadians(di1), velocity));
	scene->addEntity(new EnemyBullet_Normal(scene, p.x, p.y, Math::toRadians(di2), velocity));
	scene->addEntity(new EnemyBullet_Normal(scene, p.x, p.y, Math::toRadians(dr1), velocity));
	scene->addEntity(new EnemyBullet_Normal(scene, p.x, p.y, Math::toRadians(dr2), velocity));
}
