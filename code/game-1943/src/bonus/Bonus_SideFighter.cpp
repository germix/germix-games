////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_SideFighter
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/bonus/Bonus_SideFighter.h>
#include <src/entities/hero/Hero.h>

Bonus_SideFighter::Bonus_SideFighter() : Bonus("side_fighter", "side_fighter")
{
}
Bonus_SideFighter::~Bonus_SideFighter()
{
}
void Bonus_SideFighter::action(Scene* scene, Hero* hero)
{
	hero->activateReinforcement();
}

