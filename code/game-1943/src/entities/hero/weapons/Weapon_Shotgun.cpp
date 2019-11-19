////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Weapon_Shotgun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/weapons/Weapon_Shotgun.h>
#include <src/Scene.h>
#include <src/entities/hero/bullets/HeroBullet_Shotgun.h>

#include <mach/Math.h>

Weapon_Shotgun::Weapon_Shotgun()
{
}
Weapon_Shotgun::~Weapon_Shotgun()
{
}
const char* Weapon_Shotgun::name() const
{
	return "SHOTGUN";
}
double Weapon_Shotgun::delay() const
{
	return 0.3;
}
double Weapon_Shotgun::continuity() const
{
	return -1;
}
void Weapon_Shotgun::shoot(Scene* scene, double x, double y, bool isStrong, bool isReinforced)
{
	scene->addEntity(new HeroBullet_Shotgun(scene, x, y, Math::atan2(-1.0, 0.0), 2, isStrong));
	scene->addEntity(new HeroBullet_Shotgun(scene, x, y, Math::atan2(-1.0, -0.5), 1, isStrong));
	scene->addEntity(new HeroBullet_Shotgun(scene, x, y, Math::atan2(-1.0, +0.5), 1, isStrong));
	scene->addEntity(new HeroBullet_Shotgun(scene, x, y, Math::atan2(-1.0, -1.0), 1, isStrong));
	scene->addEntity(new HeroBullet_Shotgun(scene, x, y, Math::atan2(-1.0, +1.0), 1, isStrong));
	if(isReinforced)
	{
		scene->addEntity(new HeroBullet_Shotgun(scene, x, y, Math::atan2(-1.0, -1.5), 1, isStrong));
		scene->addEntity(new HeroBullet_Shotgun(scene, x, y, Math::atan2(-1.0, +1.5), 1, isStrong));
	}
}
