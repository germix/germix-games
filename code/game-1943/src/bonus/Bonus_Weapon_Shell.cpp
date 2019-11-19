////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Weapon_Shell
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/bonus/Bonus_Weapon_Shell.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/weapons/Weapon_Shell.h>

Bonus_Weapon_Shell::Bonus_Weapon_Shell() : Bonus("shell", "weapon.shell")
{
}
Bonus_Weapon_Shell::~Bonus_Weapon_Shell()
{
}
void Bonus_Weapon_Shell::action(Scene* scene, Hero* hero)
{
	hero->setSecondaryWeapon(new Weapon_Shell());
}
