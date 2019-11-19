////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ExplosiveBurst
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/explosions/ExplosiveBurst.h>
#include <src/Scene.h>

ExplosiveBurst::ExplosiveBurst(Scene* s) : Explosion(s, 0, 0)
, clock(0)
{
}
ExplosiveBurst::~ExplosiveBurst()
{
}
void ExplosiveBurst::update(double dt)
{
	if(clock.update(dt))
	{
		std::vector<Explosion*> e = explosionsQueue.front();
		
		for(unsigned int i = 0; i < e.size(); i++)
		{
			scene->addEntity(e[i]);
		}
		clock.reset(timesQueue.front());

		timesQueue.pop();
		explosionsQueue.pop();
		if(explosionsQueue.empty())
		{
			removable = true;
		}
	}
}
void ExplosiveBurst::render(Graphics* gr)
{
}
void ExplosiveBurst::addExplosions(double time, const std::vector<Explosion*>& explosions)
{
	timesQueue.push(time);
	explosionsQueue.push(explosions);
}

