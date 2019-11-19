////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Pineapple
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Pineapple.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

Bonus_Pineapple::Bonus_Pineapple(Scene* s, double x, double y) : Bonus_Fruit(s, x, y, 6, 16, res.findTexture("Bonus.Pineapple"))
{
}
Bonus_Pineapple::~Bonus_Pineapple()
{
}
void Bonus_Pineapple::activated(Hero* h)
{
	h->addScore(200, 3);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 200));
}

