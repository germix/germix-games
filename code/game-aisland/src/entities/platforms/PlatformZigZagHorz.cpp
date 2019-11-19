////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformZigZagHorz
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/platforms/PlatformZigZagHorz.h>
#include <src/entities/hero/Hero.h>
#include <src/Scene.h>
#include <src/EntityParameters.h>

PlatformZigZagHorz::PlatformZigZagHorz(Scene* s, double x, double y, const EntityParameters& params) : PlatformZigZag(s, x, y, params, 1, params.get("Min", "0").toInt(), params.get("Max", "0").toInt(), x)
{
}
PlatformZigZagHorz::~PlatformZigZagHorz()
{
}
void PlatformZigZagHorz::update(double dt)
{
	double oldPosition = position;
	
	PlatformZigZag::update(dt);
	
	pos.x = position;
	if(hero != null)
	{
		hero->setPositionY(pos.y);
		hero->translatePositionX(position - oldPosition);
	}
	if(scene->getCameraRect().getMinX() > max+width)
	{
		removable = true;
	}
}
