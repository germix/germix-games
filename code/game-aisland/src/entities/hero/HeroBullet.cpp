////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBullet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/HeroBullet.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>

#include <gamelib-sprites/Sprite.h>

HeroBullet::HeroBullet(Scene* s, double x, double y, double vx, double py, Sprite* spr) : Entity(s, x, y)
, stopped(false)
, velocity(vx, py)
, sprite(spr)
, spriteIndex(0)
, spriteClock(0.05)
{
}
HeroBullet::~HeroBullet()
{
}
Rectanglef HeroBullet::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef HeroBullet::bounds(double px, double py) const
{
	return Rectanglef(px - 6, py - 6, 12, 12);
}
void HeroBullet::update(double dt)
{
	unsigned int collisionFlags = scene->moveEntity(this, dt, pos, velocity, Scene::GRAVITY_ACCELERATION, false, MAP_TERRAIN_SOLID);
	if(0 != collisionFlags)
	{
		removable = true;
	}
	else
	{
		if(spriteClock.update(dt))
		{
			spriteIndex++;
			if(spriteIndex >= sprite->count())
				spriteIndex = 0;
		}
		if(!scene->getCameraRect().intersects(bounds()))
		{
			removable = true;
		}
	}
}
void HeroBullet::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteIndex, (velocity.x > 0) ? 0 : Sprite::FLIP_X);
}

