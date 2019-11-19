////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Gamepad
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Gamepad.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

Bonus_Gamepad::Bonus_Gamepad(Scene* s, double x, double y) : Bonus(s, x, y, 8, 8, res.findTexture("Bonus.Gamepad"))
{
}
Bonus_Gamepad::~Bonus_Gamepad()
{
}
void Bonus_Gamepad::activated(Hero* h)
{
	h->addScore(1000, 0);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 1000));
}

