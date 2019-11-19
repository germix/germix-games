////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Milk
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Milk.h>
#include <src/ResourceManager.h>
#include <src/entities/hero/Hero.h>

Bonus_Milk::Bonus_Milk(Scene* s, double x, double y) : Bonus(s, x, y, 5, 16, res.findTexture("Bonus.Milk"))
{
}
Bonus_Milk::~Bonus_Milk()
{
}
void Bonus_Milk::activated(Hero* h)
{
	h->setFullHealth();
}
