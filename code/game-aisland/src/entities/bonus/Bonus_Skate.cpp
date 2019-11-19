////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Skate
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Skate.h>
#include <src/ResourceManager.h>
#include <src/entities/hero/Hero.h>

Bonus_Skate::Bonus_Skate(Scene* s, double x, double y) : Bonus(s, x, y, 12, 7, res.findTexture("Bonus.Skate"))
{
}
Bonus_Skate::~Bonus_Skate()
{
}
void Bonus_Skate::activated(Hero* h)
{
	h->setSkate();
}
