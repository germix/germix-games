////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Fireball
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Fireball.h>
#include <src/ResourceManager.h>
#include <src/entities/hero/Hero.h>

Bonus_Fireball::Bonus_Fireball(Scene* s, double x, double y) : Bonus(s, x, y, 5, 16, res.findTexture("Bonus.Fireball"))
{
}
Bonus_Fireball::~Bonus_Fireball()
{
}
void Bonus_Fireball::activated(Hero* h)
{
	h->setWeapon(Hero::WEAPON_FIREBALL);
}
