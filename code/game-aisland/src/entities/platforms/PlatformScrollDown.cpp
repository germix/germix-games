////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformScrollDown
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/platforms/PlatformScrollDown.h>
#include <src/entities/hero/Hero.h>
#include <src/Scene.h>

PlatformScrollDown::PlatformScrollDown(Scene* s, double x, double y, const EntityParameters& params) : Platform(s, x, y, params, 40)
{
}
PlatformScrollDown::~PlatformScrollDown()
{
}
void PlatformScrollDown::update(double dt)
{
	pos.y += velocity*dt;
	if(hero != null)
	{
		hero->setPositionY(pos.y);
	}
	if(pos.y-32 > scene->getCameraRect().getMaxY())
	{
		releaseHero();
		pos.y = -16;
	}
	if(pos.x+width < scene->getCameraRect().getMinX())
		removable = true;
}