////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Carrot
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Carrot.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

Bonus_Carrot::Bonus_Carrot(Scene* s, double x, double y) : Bonus_Fruit(s, x, y, 5, 16, res.findTexture("Bonus.Carrot"))
{
}
Bonus_Carrot::~Bonus_Carrot()
{
}
void Bonus_Carrot::activated(Hero* h)
{
	h->addScore(100, 2);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 100));
}

