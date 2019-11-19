////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusClock
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/BonusClock.h>
#include <src/Config.h>
#include <src/Scene.h>

BonusClock::BonusClock(Map* m, Scene* s, int x, int y) : Bonus(m, s, x, y, BONUS_CLOCK, Config::auBonusActivated)
{
}
BonusClock::~BonusClock()
{
}
void BonusClock::activated(HeroTank* hero)
{
	//
	// Pausar todos los tanques enemigos
	//
	scene->pauseEnemies();
}

