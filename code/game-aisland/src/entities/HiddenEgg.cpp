////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HiddenEgg
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/HiddenEgg.h>
#include <src/Config.h>
#include <src/Scene.h>
#include <src/entities/Egg.h>

#include <mach/Color.h>
#include <mach/Graphics.h>

HiddenEgg::HiddenEgg(Scene* s, double x, double y, const String& ___bonus) : Entity(s, x, y)
, bonus(___bonus)
, dropped(false)
{
}
HiddenEgg::~HiddenEgg()
{
}
void HiddenEgg::update(double dt)
{
	if(scene->getCameraRect().getMinX() > bounds().getMaxX())
	{
		removable = true;
	}
}
void HiddenEgg::render(Graphics* gr)
{
	if(Debug::showCollisionRect)
	{
		gr->drawRect(bounds(), Color(255,0,0));
	}
}
Rectanglef HiddenEgg::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef HiddenEgg::bounds(double px, double py) const
{
	return Rectanglef(px - 14, py - 8, 28, 8);
}
Rectanglef HiddenEgg::getCollisionRectangle() const
{
	if(dropped)
		return Rectanglef();
	return bounds();
}
void HiddenEgg::drop()
{
	if(!dropped)
	{
		scene->addEntity(new Egg(scene, pos.x, pos.y, bonus));
		dropped = true;
		removable = true;
	}
}

