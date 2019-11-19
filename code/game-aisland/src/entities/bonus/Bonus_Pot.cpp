////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Pot
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Pot.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

Bonus_Pot::Bonus_Pot(Scene* s, double x, double y) : Bonus(s, x, y, 8, 24, res.findTexture("Bonus.Pot"))
{
}
Bonus_Pot::~Bonus_Pot()
{
}
void Bonus_Pot::activated(Hero* h)
{
	h->setPot();
	h->addScore(1000, 0);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 1000));
}

