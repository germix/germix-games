////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Weapon_Auto
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/weapons/Weapon_Auto.h>
#include <src/Scene.h>
#include <src/entities/hero/bullets/HeroBullet_Auto.h>

#include <mach/Math.h>

Weapon_Auto::Weapon_Auto()
{
}
Weapon_Auto::~Weapon_Auto()
{
}
const char* Weapon_Auto::name() const
{
	return "AUTO";
}
double Weapon_Auto::delay() const
{
	return 0.06;
}
double Weapon_Auto::continuity() const
{
	return 0.9;
}
void Weapon_Auto::shoot(Scene* scene, double x, double y, bool isStrong, bool isReinforced)
{
	double dx = (16/2)+5;
	double angle = Math::atan2(-1.0, 0.0);
	if(!isReinforced)
	{
		scene->addEntity(new HeroBullet_Auto(scene, x, y, angle));
	}
	else
	{
		scene->addEntity(new HeroBullet_Auto(scene, x - dx, y, angle));
		scene->addEntity(new HeroBullet_Auto(scene, x + dx, y, angle));
	}
}

