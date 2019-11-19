////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Weapon_3way
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/bonus/Bonus_Weapon_3way.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/weapons/Weapon_3way.h>

Bonus_Weapon_3way::Bonus_Weapon_3way() : Bonus("3way", "weapon.3way")
{
}
Bonus_Weapon_3way::~Bonus_Weapon_3way()
{
}
void Bonus_Weapon_3way::action(Scene* scene, Hero* hero)
{
	hero->setSecondaryWeapon(new Weapon_3way());
}
