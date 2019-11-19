////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformFallDown
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/platforms/PlatformFallDown.h>
#include <src/entities/hero/Hero.h>
#include <src/Scene.h>

PlatformFallDown::PlatformFallDown(Scene* s, double x, double y, const EntityParameters& params) : Platform(s, x, y, params, 100)
, started(false)
{
}
PlatformFallDown::~PlatformFallDown()
{
}
void PlatformFallDown::update(double dt)
{
	if(hero != null)
	{
		started = true;
	}
	if(started)
	{
		pos.y += velocity*dt;
		
		if(hero != null)
		{
			hero->setPositionY(pos.y);
		}
		if(pos.y-128 > scene->getCameraRect().getMaxY())
		{
			removable = true;
		}
	}
	if(pos.x+width < scene->getCameraRect().getMinX())
		removable = true;
}
