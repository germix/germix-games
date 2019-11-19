////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusHelmet
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/BonusHelmet.h>
#include <src/Config.h>
#include <src/entities/tanks/HeroTank.h>

BonusHelmet::BonusHelmet(Map* m, Scene* s, int x, int y) : Bonus(m, s, x, y, BONUS_HELMET, Config::auBonusActivated)
{
}
BonusHelmet::~BonusHelmet()
{
}
void BonusHelmet::activated(HeroTank* hero)
{
	//
	// Activar el escudo del h�roe
	//
	hero->activateHelmet(10);
}

