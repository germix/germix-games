////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BombThrower | Controlador del lanzamiento de bombas
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/BombThrower.h>
#include <src/entities/hero/bombs/StielHandGranate.h>
#include <src/scene/Scene.h>

#define INITIAL_BOMBS 10

BombThrower::BombThrower(bool infinite) : count(INITIAL_BOMBS), infiniteBombs(infinite)
{
}
BombThrower::~BombThrower()
{
}
void BombThrower::reset()
{
	count = 10;
}
void BombThrower::addBombs(int bombs)
{
	count += bombs;
}
bool BombThrower::throwBomb(Scene* scene, double posX, double posY, double velocityX, double velocityY)
{
	if(count > 0)
	{
		scene->addEntity(new StielHandGranate(
				scene,
				posX,
				posY,
				velocityX,
				velocityY));
		
		if(!infiniteBombs)
			count--;
		return true;
	}
	return false;
}