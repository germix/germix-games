////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Energy_Yashichi
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/bonus/Bonus_Energy_Yashichi.h>
#include <src/entities/hero/Hero.h>

Bonus_Energy_Yashichi::Bonus_Energy_Yashichi() : Bonus("yashichi", "energy.yashichi")
{
}
Bonus_Energy_Yashichi::~Bonus_Energy_Yashichi()
{
}
void Bonus_Energy_Yashichi::action(Scene* scene, Hero* hero)
{
	hero->setHealth(hero->getMaxHealth());
}

