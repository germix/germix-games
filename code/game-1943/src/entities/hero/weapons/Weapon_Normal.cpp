////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Weapon_Normal
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/weapons/Weapon_Normal.h>
#include <src/Scene.h>
#include <src/entities/hero/bullets/HeroBullet_Normal.h>

#include <mach/Math.h>

Weapon_Normal::Weapon_Normal()
{
}
Weapon_Normal::~Weapon_Normal()
{
}
const char* Weapon_Normal::name() const
{
	return "NORMAL";
}
double Weapon_Normal::delay() const
{
	return 0.3;
}
double Weapon_Normal::continuity() const
{
	return -1;
}
void Weapon_Normal::shoot(Scene* scene, double x, double y, bool isStrong, bool isReinforced)
{
	double dx = (16/2)+5;
	double angle = Math::atan2(-1.0, 0.0);
	if(!isReinforced)
	{
		scene->addEntity(new HeroBullet_Normal(scene, x, y, angle));
	}
	else
	{
		scene->addEntity(new HeroBullet_Normal(scene, x - dx, y, angle));
		scene->addEntity(new HeroBullet_Normal(scene, x + dx, y, angle));
	}
}

