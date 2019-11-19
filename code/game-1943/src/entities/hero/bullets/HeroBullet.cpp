////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBullet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/bullets/HeroBullet.h>
#include <src/Scene.h>

#include <mach/Math.h>

HeroBullet::HeroBullet(Scene* s, double x, double y, Sprite* sprite, double angle, double ___length, double velocity, int ___damageToEnemy, int ___damageToBullet) : Bullet(s, x, y, sprite, angle, velocity)
, length(___length)
, damageToEnemy(___damageToEnemy)
, damageToBullet(___damageToBullet)
, initialPos(pos)
{
}
HeroBullet::~HeroBullet()
{
}
void HeroBullet::update(double dt)
{
	pos.x += Math::cos(angle)*(velocity*dt);
	pos.y += Math::sin(angle)*(velocity*dt);

	if(!scene->getSceneRect().intersects(rect())
		|| (length > 0 && length < pos.getDistanceOf(initialPos)))
	{
		removable = true;
	}
}
void HeroBullet::destroy()
{
	// TODO: Mejorar esto
	removable = true;
	destroyed = true;
}
int HeroBullet::getDamageToEnemy() const
{
	return damageToEnemy;
}
int HeroBullet::getDamageToBullet() const
{
	return damageToBullet;
}
