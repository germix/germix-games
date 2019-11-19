////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Weapon_Shotgun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/bonus/Bonus_Weapon_Shotgun.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/weapons/Weapon_Shotgun.h>

Bonus_Weapon_Shotgun::Bonus_Weapon_Shotgun() : Bonus("shotgun", "weapon.shotgun")
{
}
Bonus_Weapon_Shotgun::~Bonus_Weapon_Shotgun()
{
}
void Bonus_Weapon_Shotgun::action(Scene* scene, Hero* hero)
{
	hero->setSecondaryWeapon(new Weapon_Shotgun());
}
