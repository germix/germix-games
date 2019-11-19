////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Tank
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/Tank.h>
#include <src/Config.h>
#include <src/base/Sprite.h>
#include <src/Map.h>
#include <src/Scene.h>

#include <mach/Graphics.h>
#include <mach/Rectangle.h>

Tank::Tank(Map* m, Scene* s, int x, int y, int model, int color) : Entity(m, s, x, y)
, dir(DIRECTION_UP)
, tankModel(model)
, tankColor(color)
, sprite(null)
, animIndex(0)
{
	updateSprite();
}
Tank::~Tank()
{
}
void Tank::render(Graphics* gr)
{
	if(Debug::showTankRectangle)
	{
		gr->fillRect(x, y, width, height, Color(255,0,0));
	}
	sprite->render(gr, x, y, getSpriteIndex());
}
void Tank::updateSprite()
{
	sprite = Config::tankSprites[tankModel + (tankColor*MAX_TANK_MODELS)];
}
int Tank::getSpriteIndex() const
{
	int baseIndex = 0;
	
	switch(dir)
	{
		case DIRECTION_UP:		baseIndex = 0;	break;
		case DIRECTION_DOWN:	baseIndex = 4;	break;
		case DIRECTION_LEFT:	baseIndex = 2;	break;
		case DIRECTION_RIGHT:	baseIndex = 6;	break;
	}
	return baseIndex+animIndex;
}
bool Tank::moveVert(int dx, int dy)
{
	int rx = (x+dx)/4;
	Rectangle rc(rx*4, y, width, height);
	if(map->tryMoveTankVert(rc, dy))
	{
		y += dy;
		x = rc.getX();
		if(++animIndex == 2) animIndex = 0;
		return true;
	}
	return false;
}
bool Tank::moveHorz(int dx, int dy)
{
	int ry = (y+dy)/4;
	Rectangle rc(x, ry*4, width, height);
	if(map->tryMoveTankHorz(rc, dx))
	{
		x += dx;
		y = rc.getY();
		if(++animIndex == 2) animIndex = 0;
		return true;
	}
	return false;
}
Point Tank::getShootPosition(Direction dir) const
{
	int dx = 0;
	int dy = 0;
	
	switch(dir)
	{
		case DIRECTION_UP:
			dx = width/2;
			dy = 0;
			break;
		case DIRECTION_DOWN:
			dx = width/2;
			dy = height;
			break;
		case DIRECTION_LEFT:
			dx = 0;
			dy = height/2;
			break;
		case DIRECTION_RIGHT:
			dx = width;
			dy = height/2;
			break;
	}
	return Point(x+dx, y+dy);
}
bool Tank::move(int dx, int dy)
{
	if(scene->tryMove(this, dx, dy))
	{
		if(dy != 0)
		{
			if(moveVert(0, dy)) return true;
			else if(moveVert(4, dy)) return true;
		}
		else if(dx != 0)
		{
			if(moveHorz(dx, 0)) return true;
			else if(moveHorz(dx, 4)) return true;
		}
	}
	return false;
}
void Tank::selectTankModel(int model)
{
	tankModel = model;
	updateSprite();
}
void Tank::selectTankColor(int color)
{
	tankColor = color;
	updateSprite();
}
