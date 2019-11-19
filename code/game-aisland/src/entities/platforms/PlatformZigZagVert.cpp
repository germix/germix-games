////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformZigZagVert
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/platforms/PlatformZigZagVert.h>
#include <src/entities/hero/Hero.h>
#include <src/Scene.h>
#include <src/EntityParameters.h>

PlatformZigZagVert::PlatformZigZagVert(Scene* s, double x, double y, const EntityParameters& params) : PlatformZigZag(s, x, y, params, 1, params.get("Min", "0").toInt(), params.get("Max", "0").toInt(), y)
{
}
PlatformZigZagVert::~PlatformZigZagVert()
{
}
void PlatformZigZagVert::update(double dt)
{
	PlatformZigZag::update(dt);
	pos.y = position;
	if(hero != null)
	{
		hero->setPositionY(position);
	}
	if(pos.x+width < scene->getCameraRect().getMinX())
		removable = true;
}
