////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusTank
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/BonusTank.h>
#include <src/Config.h>
#include <src/entities/tanks/HeroTank.h>

BonusTank::BonusTank(Map* m, Scene* s, int x, int y) : Bonus(m, s, x, y, BONUS_TANK, Config::auNewLife)
{
}
BonusTank::~BonusTank()
{
}
void BonusTank::activated(HeroTank* hero)
{
	//
	// Agregar vida
	//
	hero->addLife();
}
