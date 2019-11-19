////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformScrollUp
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/platforms/PlatformScrollUp.h>
#include <src/entities/hero/Hero.h>
#include <src/Scene.h>

PlatformScrollUp::PlatformScrollUp(Scene* s, double x, double y, const EntityParameters& params) : Platform(s, x, y, params, 40)
{
}
PlatformScrollUp::~PlatformScrollUp()
{
}
void PlatformScrollUp::update(double dt)
{
	pos.y -= velocity*dt;
	if(hero != null)
	{
		hero->setPositionY(pos.y);
	}
	if(pos.y+16 < scene->getCameraRect().getMinY())
	{
		releaseHero();
		pos.y = scene->getCameraRect().getMaxY();
		if(hero != null)
			hero->setPositionY(scene->getCameraRect().getMinY());
	}
	if(pos.x+width < scene->getCameraRect().getMinX())
		removable = true;
}
