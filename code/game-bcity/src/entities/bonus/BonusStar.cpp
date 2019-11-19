////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusStar
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/BonusStar.h>
#include <src/Config.h>
#include <src/entities/tanks/HeroTank.h>

BonusStar::BonusStar(Map* m, Scene* s, int x, int y) : Bonus(m, s, x, y, BONUS_STAR, Config::auBonusActivated)
{
}
BonusStar::~BonusStar()
{
}
void BonusStar::activated(HeroTank* hero)
{
	//
	// Agregar estrella
	//
	hero->addStar();
}
