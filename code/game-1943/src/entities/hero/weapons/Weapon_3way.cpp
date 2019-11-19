////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Weapon_3way
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/weapons/Weapon_3way.h>
#include <src/Scene.h>
#include <src/entities/hero/bullets/HeroBullet_3way.h>

#include <mach/Math.h>

Weapon_3way::Weapon_3way()
{
}
Weapon_3way::~Weapon_3way()
{
}
const char* Weapon_3way::name() const
{
	return "3 WAY";
}
double Weapon_3way::delay() const
{
	return 0.3;
}
double Weapon_3way::continuity() const
{
	return -1;
}
void Weapon_3way::shoot(Scene* scene, double x, double y, bool isStrong, bool isReinforced)
{
	scene->addEntity(new HeroBullet_3way(scene, x, y, Math::atan2(-1.0, 0.0), 0));
	scene->addEntity(new HeroBullet_3way(scene, x, y, Math::atan2(-1.0, -0.6), -1));
	scene->addEntity(new HeroBullet_3way(scene, x, y, Math::atan2(-1.0, +0.6), +1));
}

