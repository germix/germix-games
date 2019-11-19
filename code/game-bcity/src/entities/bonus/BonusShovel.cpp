////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusShovel
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/BonusShovel.h>
#include <src/Config.h>
#include <src/Scene.h>

BonusShovel::BonusShovel(Map* m, Scene* s, int x, int y) : Bonus(m, s, x, y, BONUS_SHOVEL, Config::auBonusActivated)
{
}
BonusShovel::~BonusShovel()
{
}
void BonusShovel::activated(HeroTank* hero)
{
	//
	// Fortificar la base
	//
	scene->fortifyBase();
}

