////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Entity
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/Entity.h>
#include <src/Scene.h>

bool Entity::move(DIRECTION dir, unsigned int mask, const Rectangle& rect)
{
	int dx = 0;
	int dy = 0;
	
	switch(dir)
	{
		case DIRECTION_UP:		dy = -1;	break;
		case DIRECTION_DOWN:	dy = +1;	break;
		case DIRECTION_LEFT:	dx = -1;	break;
		case DIRECTION_RIGHT:	dx = +1;	break;
		default:							return false;
	}
	if(scene->tryMove(rect, dx, dy, mask))
	{
		x += dx;
		y += dy;
		return true;
	}
	return false;
}

