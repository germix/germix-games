////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Weapon_Auto
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/bonus/Bonus_Weapon_Auto.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/weapons/Weapon_Auto.h>


Bonus_Weapon_Auto::Bonus_Weapon_Auto() : Bonus("auto", "weapon.auto")
{
}
Bonus_Weapon_Auto::~Bonus_Weapon_Auto()
{
}
void Bonus_Weapon_Auto::action(Scene* scene, Hero* hero)
{
	hero->setSecondaryWeapon(new Weapon_Auto());
}
