////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_ExtraLife
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_ExtraLife.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>

Bonus_ExtraLife::Bonus_ExtraLife(Scene* s, double x, double y) : Bonus(s, x, y, 4, 14, res.findTexture("Bonus.ExtraLife"))
{
}
Bonus_ExtraLife::~Bonus_ExtraLife()
{
}
void Bonus_ExtraLife::activated(Hero* h)
{
	h->addLife();
}

