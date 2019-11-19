////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/Bonus.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>

#include <mach/Mixer.h>
#include <mach/Texture.h>
#include <mach/Graphics.h>

Bonus::Bonus(Scene* s, double x, double y, int ___dx, int ___dy, Texture* tex) : Entity(s, x, y)
, dx(___dx)
, dy(___dy)
, texture(tex)
{
}
Bonus::~Bonus()
{
}
void Bonus::update(double dt)
{
	if(pos.x+texture->getWidth() < scene->getCameraRect().getMinX())
	{
		removable = true;
	}
}
void Bonus::render(Graphics* gr)
{
	gr->drawTexture(texture, int(pos.x - dx), int(pos.y - dy));
}
void Bonus::collides(Entity* e)
{
	if(dynamic_cast<Hero*>(e))
	{
		removable = true;
		Mixer::playChannel(res.findSound("Bonus"));
		activated((Hero*)e);
	}
}
Rectanglef Bonus::bounds(double px, double py) const
{
	return Rectanglef(px - dx, py - dy, texture->getWidth(), texture->getHeight());
}
