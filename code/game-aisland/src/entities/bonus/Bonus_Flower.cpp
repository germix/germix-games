////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Flower
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Flower.h>
#include <src/ResourceManager.h>
#include <src/entities/hero/Hero.h>

Bonus_Flower::Bonus_Flower(Scene* s, double x, double y) : Bonus(s, x, y, 6, 16, res.findTexture("Bonus.Flower"))
{
}
Bonus_Flower::~Bonus_Flower()
{
}
void Bonus_Flower::activated(Hero* h)
{
	h->addScore(500, 0);
}

