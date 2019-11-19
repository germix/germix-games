////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformMoveTo
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/platforms/PlatformMoveTo.h>
#include <src/entities/hero/Hero.h>
#include <src/Scene.h>
#include <src/EntityParameters.h>

#include <mach/String.h>

PlatformMoveTo::PlatformMoveTo(Scene* s, double x, double y, const EntityParameters& params) : Platform(s, x, y, params, 40)
, to(0)
, mode(MODE_UNKNOWN)
, active(false)
{
	String sz = params.get("To", "");
	if(!sz.empty())
	{
		to = sz.toInt();
		sz = params.get("Mode", "");
		if(sz == "ToUp")			mode = MODE_UP;
		else if(sz == "ToDown")		mode = MODE_DOWN;
		else if(sz == "ToLeft")		mode = MODE_LEFT;
		else if(sz == "ToRight")	mode = MODE_RIGHT;
	}
}
PlatformMoveTo::~PlatformMoveTo()
{
}
void PlatformMoveTo::update(double dt)
{
	if(active)
	{
		if(mode != MODE_UNKNOWN && mode != MODE_STOPPED)
		{
			switch(mode)
			{
				case MODE_UP:
					pos.y -= velocity*dt;
					if(pos.y < to)
					{
						pos.y = to;
						mode = MODE_STOPPED;
					}
					if(hero != null)
						hero->setPositionY(pos.y);
					break;
				case MODE_DOWN:
					pos.y += velocity*dt;
					if(pos.y >= to)
					{
						pos.y = to;
						mode = MODE_STOPPED;
					}
					if(hero != null)
						hero->setPositionY(pos.y);
					break;
				case MODE_LEFT:
					{
						double o = pos.x;
						pos.x -= velocity*dt;
						if(pos.x < to)
						{
							pos.x = to;
							mode = MODE_STOPPED;
						}
						if(hero != null)
							hero->translatePositionX(pos.x - o);
					}
					break;
				case MODE_RIGHT:
					{
						double o = pos.x;
						pos.x += velocity*dt;
						if(pos.x >= to)
						{
							pos.x = to;
							mode = MODE_STOPPED;
						}
						if(hero != null)
							hero->translatePositionX(pos.x - o);
					}
				default:
					break;
				
			}
		}
	}
	else
	{
		if(hero != null)
		{
			active = true;
		}
	}
	if(pos.x+width < scene->getCameraRect().getMinX())
		removable = true;
}
