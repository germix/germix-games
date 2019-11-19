////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusGrenade
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/BonusGrenade.h>
#include <src/Config.h>
#include <src/Scene.h>

#include <mach/Mixer.h>

BonusGrenade::BonusGrenade(Map* m, Scene* s, int x, int y) : Bonus(m, s, x, y, BONUS_GRENADE, Config::auBonusActivated)
{
}
BonusGrenade::~BonusGrenade()
{
}
void BonusGrenade::activated(HeroTank* hero)
{
	//
	// Eliminar todos los tanques enemigos
	//
	scene->killEnemies();
	
	Mixer::playChannel(Config::auEnemeyDead);
}

