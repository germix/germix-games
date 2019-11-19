////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PlatformZigZag
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/platforms/PlatformZigZag.h>

PlatformZigZag::PlatformZigZag(Scene* s, double x, double y, const EntityParameters& params, int dir, int min, int max, double pos) : Platform(s, x, y, params, 40)
{
	this->dir = dir;
	this->min = min;
	this->max = max;
	this->position = pos;
}
PlatformZigZag::~PlatformZigZag()
{
}
void PlatformZigZag::update(double dt)
{
	if(dir == 1)
	{
		position += velocity*dt;
		
		if(position >= max)
		{
			dir = -1;
			position = max;
		}
	}
	else
	{
		position -= velocity*dt;
		
		if(position <= min)
		{
			dir = +1;
			position = min;
		}
	}
}
