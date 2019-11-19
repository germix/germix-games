////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Banana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Banana.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

Bonus_Banana::Bonus_Banana(Scene* s, double x, double y) : Bonus_Fruit(s, x, y, 8, 14, res.findTexture("Bonus.Banana"))
{
}
Bonus_Banana::~Bonus_Banana()
{
}
void Bonus_Banana::activated(Hero* h)
{
	h->addScore(50, 1);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 50));
}

