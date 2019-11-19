////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Platform
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/platforms/Platform.h>
#include <src/ResourceManager.h>
#include <src/EntityParameters.h>

#include <mach/Color.h>
#include <mach/Graphics.h>

Platform::Platform(Scene* s, double x, double y, const EntityParameters& params, double vel)
: Entity(s, x, y)
, hero(null)
, width(8*8)
, height(8*2)
, texture(null)
, velocity(vel)
{
	texture = res.findTexture(params.get("Image", "").c_str());
}
Platform::~Platform()
{
}
void Platform::render(Graphics* gr)
{
	if(texture == null)
	{
		gr->fillRect(bounds(), Color(0,0,0));
	}
	else
	{
		gr->drawTexture(texture, int(pos.x), int(pos.y));
	}
}
