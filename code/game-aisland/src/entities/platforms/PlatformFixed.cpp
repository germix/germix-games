////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformFixed
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/platforms/PlatformFixed.h>
#include <src/Scene.h>

PlatformFixed::PlatformFixed(Scene* s, double x, double y, const EntityParameters& params) : Platform(s, x, y, params, 0)
{
}
PlatformFixed::~PlatformFixed()
{
}
void PlatformFixed::update(double dt)
{
	if(pos.x+width < scene->getCameraRect().getMinX())
		removable = true;
}
