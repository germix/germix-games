////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemyWeaponHandler
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/EnemyWeaponHandler.h>
#include <src/entities/enemies/weapons/EnemyWeapon.h>

#include <mach/Vector2f.h>

EnemyWeaponHandler::EnemyWeaponHandler(EnemyWeapon* w, double shootTime, int bulletVelocity)
: weapon(w)
, clock(shootTime)
, velocity(bulletVelocity)
{
}
EnemyWeaponHandler::~EnemyWeaponHandler()
{
	delete weapon;
}
void EnemyWeaponHandler::update(Scene* scene, double x, double y, double dt)
{
	if(clock.update(dt))
	{
		weapon->shoot(scene, Vector2f(x,y), velocity);
	}
}
