////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformFallUp
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/platforms/PlatformFallUp.h>
#include <src/entities/hero/Hero.h>
#include <src/Scene.h>

PlatformFallUp::PlatformFallUp(Scene* s, double x, double y, const EntityParameters& params) : Platform(s, x, y, params, 100)
, started(false)
{
}
PlatformFallUp::~PlatformFallUp()
{
}
void PlatformFallUp::update(double dt)
{
	if(hero != null)
	{
		started = true;
	}
	if(started)
	{
		pos.y -= velocity*dt;
		
		if(hero != null)
		{
			hero->setPositionY(pos.y);
		}
		if(pos.y+16 < scene->getCameraRect().getMinY())
		{
			if(hero)
			{
				hero->setPositionY(scene->getCameraRect().getMinY());
				releaseHero();
			}
			removable = true;
		}
	}
	if(pos.x+width < scene->getCameraRect().getMinX())
		removable = true;
}
