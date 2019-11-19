////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RShobuBomb | Bomba del helicóptero R-Shobu
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/rshobu/RShobuBomb.h>
#include <src/Debug.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/NormalExplosionS.h>
#include <src/entities/effects/GrenadeExplosionBig.h>

#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define MAX_VELOCITY 120

RShobuBomb::RShobuBomb(Scene* scene, double x, double y) : EnemyProjectile(scene, x, y)
, vel()
, accel(0, GRAVITY_DOWN*GRAVITY_CONSTANT)
, dir(1)
, sprite(null)
, spriteFrame(0)
, spriteClock(0.018)
{
	sprite = res.findSpriteSheet("RShobuBomb")->getSprite();
}
RShobuBomb::~RShobuBomb()
{
}
void RShobuBomb::update(double dt)
{
	CollisionInfo ci = scene->moveEntity(this, dt, pos, vel, accel, false, MAP_TERRAIN_SOLID);
	
	if(vel.y > MAX_VELOCITY)
	{
		vel.y = MAX_VELOCITY;
	}
	bool exploit = false;
	
	if(ci.flags & COLLISION_FLAG_BOTTOM)
	{
		exploit = true;
	}
	//
	// ...
	//
	if(exploit)
	{
		removable = true;
		scene->addEntity(new GrenadeExplosionBig(scene, pos.x, pos.y));
	}
	else
	{
		if(spriteClock.update(dt))
		{
			spriteFrame += dir;
			if(dir < 0)
			{
				if(spriteFrame < 0)
				{
					dir = +1;
					spriteFrame = 0;
				}
			}
			else if(dir > 0)
			{
				if(spriteFrame >= sprite->count())
				{
					dir = -1;
					spriteFrame = sprite->count()-1;
				}
			}
		}
	}
}
void RShobuBomb::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteFrame, 0);
	if(Debug::showBulletRects)
	{
		gr->drawRect(bounds(), Debug::colorBulletRects);
	}
}
Rectanglef RShobuBomb::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef RShobuBomb::bounds(double px, double py) const
{
	return sprite->rectangle(px, py, spriteFrame, 0);
}
void RShobuBomb::hurt(int damage)
{
	removable = true;
	scene->getHero()->addScore(10);
	scene->addEntity(new NormalExplosionS(scene, pos.x, pos.y));
}
bool RShobuBomb::isHurtable() const
{
	return true;
}
Rectanglef RShobuBomb::hurtableRect() const
{
	return bounds();
}
void RShobuBomb::collide(Entity* other)
{
	if(dynamic_cast<Hero*>(other))
	{
		removable = true;
		((Hero*)other)->hurt();
		scene->addEntity(new GrenadeExplosionBig(scene, pos.x, pos.y));
	}
}
Rectanglef RShobuBomb::collisionRect() const
{
	return bounds();
}

