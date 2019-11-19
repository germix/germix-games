////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Weapon_Laser
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/bonus/Bonus_Weapon_Laser.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/weapons/Weapon_Laser.h>

Bonus_Weapon_Laser::Bonus_Weapon_Laser() : Bonus("laser", "weapon.laser")
{
}
Bonus_Weapon_Laser::~Bonus_Weapon_Laser()
{
}
void Bonus_Weapon_Laser::action(Scene* scene, Hero* hero)
{
	hero->setSecondaryWeapon(new Weapon_Laser());
}
