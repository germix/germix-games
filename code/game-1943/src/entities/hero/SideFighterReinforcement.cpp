////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SideFighterReinforcement
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/SideFighterReinforcement.h>
#include <src/entities/hero/SideFighter.h>

SideFighterReinforcement::SideFighterReinforcement(Scene* scene, Hero* hero)
{
	fighters[0] = new SideFighter(scene, hero, Direction_Left);
	fighters[1] = new SideFighter(scene, hero, Direction_Right);
}
SideFighterReinforcement::~SideFighterReinforcement()
{
	delete fighters[0];
	delete fighters[1];
}
bool SideFighterReinforcement::update(double dt)
{
	for(int i = 0; i < MAX_SIDE_FIGHTERS; i++)
	{
		fighters[i]->update(dt);
		if(fighters[i]->isDestroyed())
		{
			//
			// Con que tan uno solo sea removible, se elimina todo el refuerzo
			//
			return true;
		}
	}
	return false;
}
void SideFighterReinforcement::render(Graphics* gr)
{
	for(int i = 0; i < MAX_SIDE_FIGHTERS; i++)
	{
		fighters[i]->render(gr);
	}
}
bool SideFighterReinforcement::checkHit(EnemyBullet* bullet)
{
	for(int i = 0; i < MAX_SIDE_FIGHTERS; i++)
	{
		fighters[i]->checkHit(bullet);
		if(fighters[i]->isDestroyed())
		{
			//
			// Con que tan uno solo sea removible, se elimina todo el refuerzo
			//
			return true;
		}
	}
	return false;
}

