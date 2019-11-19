////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus.h>
#include <src/Debug.h>
#include <src/Config.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>

#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>

Bonus::Bonus(Scene* scene, double x, double y) : Entity(scene, x, y)
, vel()
, accel(0, GRAVITY_CONSTANT*GRAVITY_DOWN)
, onGround(false)
, sprite(null)
, spriteFrame(0)
, spriteHints(0)
, spriteClock(0.04)
{
}
Bonus::~Bonus()
{
}
void Bonus::update(double dt)
{
	if(!onGround)
	{
		CollisionInfo ci = scene->moveEntity(this, dt, pos, vel, accel, onGround, MAP_TERRAIN_SOLID|MAP_TERRAIN_TOPDOWN);
		
		onGround = (ci.flags & COLLISION_FLAG_BOTTOM) != 0;
	}
	if(bounds().getMaxX() < scene->getSceneRect().getMinX())
	{
		removable = true;
	}
	else
	{
		animate(dt);
	}
}
void Bonus::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteFrame, spriteHints);
	if(Debug::showBonusRects)
	{
		gr->drawRect(bounds(), Debug::colorBonusRects);
	}
}
Rectanglef Bonus::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef Bonus::bounds(double px, double py) const
{
	return sprite->rectangle(px, py, spriteFrame, spriteHints);
}
void Bonus::collide(Entity* other)
{
//	if(onGround)
	{
		if(dynamic_cast<Hero*>(other))
		{
			activate((Hero*)other);
			removable = true;
		}
	}
}
Rectanglef Bonus::collisionRect() const
{
	return bounds();
}
