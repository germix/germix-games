////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Weapon_Shell
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/weapons/Weapon_Shell.h>
#include <src/Scene.h>
#include <src/entities/hero/bullets/HeroBullet_Shell.h>

#include <mach/Math.h>

Weapon_Shell::Weapon_Shell()
{
}
Weapon_Shell::~Weapon_Shell()
{
}
const char* Weapon_Shell::name() const
{
	return "SHELL";
}
double Weapon_Shell::delay() const
{
	return 0.1;
}
double Weapon_Shell::continuity() const
{
	return -1;
}
void Weapon_Shell::shoot(Scene* scene, double x, double y, bool isStrong, bool isReinforced)
{
	double dx = (16/2)+5;
	double angle = Math::atan2(-1.0, 0.0);
	if(!isReinforced)
	{
		scene->addEntity(new HeroBullet_Shell(scene, x, y, angle));
	}
	else
	{
		scene->addEntity(new HeroBullet_Shell(scene, x - dx, y, angle));
		scene->addEntity(new HeroBullet_Shell(scene, x + dx, y, angle));
	}
}
