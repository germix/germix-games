////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Tomato
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Tomato.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

Bonus_Tomato::Bonus_Tomato(Scene* s, double x, double y) : Bonus_Fruit(s, x, y, 7, 12, res.findTexture("Bonus.Tomato"))
{
}
Bonus_Tomato::~Bonus_Tomato()
{
}
void Bonus_Tomato::activated(Hero* h)
{
	h->addScore(50, 1);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 50));
}
