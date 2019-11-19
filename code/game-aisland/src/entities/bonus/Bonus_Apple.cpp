////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Apple
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Apple.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

Bonus_Apple::Bonus_Apple(Scene* s, double x, double y) : Bonus_Fruit(s, x, y, 7, 15, res.findTexture("Bonus.Apple"))
{
}
Bonus_Apple::~Bonus_Apple()
{
}
void Bonus_Apple::activated(Hero* h)
{
	h->addScore(50, 1);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 50));
}

