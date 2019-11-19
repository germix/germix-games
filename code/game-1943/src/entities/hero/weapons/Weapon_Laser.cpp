////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Weapon_Laser
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/weapons/Weapon_Laser.h>
#include <src/Scene.h>
//#include <src/entities/hero/bullets/HeroBullet_Laser.h>

#include <mach/Math.h>

Weapon_Laser::Weapon_Laser()
{
}
Weapon_Laser::~Weapon_Laser()
{
}
const char* Weapon_Laser::name() const
{
	return "LASER";
}
double Weapon_Laser::delay() const
{
	return 0;
}
double Weapon_Laser::continuity() const
{
	return -1;
}
void Weapon_Laser::shoot(Scene* scene, double x, double y, bool isStrong, bool isReinforced)
{
}
