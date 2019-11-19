////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Energy_Tank
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/bonus/Bonus_Energy_Tank.h>
#include <src/entities/hero/Hero.h>

Bonus_Energy_Tank::Bonus_Energy_Tank() : Bonus("tank", "energy.tank")
{
}
Bonus_Energy_Tank::~Bonus_Energy_Tank()
{
}
void Bonus_Energy_Tank::action(Scene* scene, Hero* hero)
{
	hero->addHealth(40);
}


