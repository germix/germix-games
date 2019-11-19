////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyBullet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/bullets/EnemyBullet.h>
#include <src/Scene.h>

#include <mach/Math.h>

EnemyBullet::EnemyBullet(Scene* s, double x, double y, Sprite* sprite, double angle, double velocity, int ___damage) : Bullet(s, x, y, sprite, angle, velocity)
, damage(___damage)
{
}
EnemyBullet::~EnemyBullet()
{
}
void EnemyBullet::update(double dt)
{
	pos.x += Math::cos(angle)*(velocity*dt);
	pos.y += Math::sin(angle)*(velocity*dt);

	if(!scene->getSceneRect().intersects(rect()))
	{
		removable = true;
	}
}
int EnemyBullet::collisioned()
{
	destroyed = true;
	removable = true;
	return damage;
}
