////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RocketLauncherBullet | Cohete lanzado por RocketLauncher
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/weapons/RocketLauncherBullet.h>
#include <src/Debug.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/BulletHit2.h>
#include <src/entities/effects/NormalExplosionS.h>
#include <src/___/HurtableRect.h>

#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define MAX_VELOCITY		1200
#define MAX_ACCELERATION	800
#define INCR_ACCELERATION	120

RocketLauncherBullet::RocketLauncherBullet(Scene* scene, double x, double y, int shotAngle, int lookX) : HeroBullet(scene, x, y)
, vel(0, 0)
, accel(0, 0)
, sprite(null)
, spriteFrame(0)
, spriteHints(0)
, spriteClock(0.02)
, dirX(0)
, dirY(0)
{
	if(shotAngle == 0)
	{
		dirX = lookX;
		sprite = res.findSpriteSheet("Bullet.R")->getSprite("Horz");
		if(lookX == -1)
			spriteHints |= Sprite::FLIP_X;
	}
	else
	{
		dirY = -1;
		sprite = res.findSpriteSheet("Bullet.R")->getSprite("Vert");
		if(lookX == -1)
			spriteHints |= Sprite::FLIP_X;
		if(shotAngle == -90)
		{
			dirY = +1;
			spriteHints |= Sprite::FLIP_Y;
		}
	}
}
RocketLauncherBullet::~RocketLauncherBullet()
{
}
void RocketLauncherBullet::update(double dt)
{
	CollisionInfo ci =  scene->moveEntity(this, dt, pos, vel, accel, false, MAP_TERRAIN_SOLID);
	
	if(ci.flags)
	{
		//
		// Eliminar si colisionó con el escenario
		//
		removable = true;
		scene->addEntity(new BulletHit2(scene, pos.x, pos.y));
	}
	else if(scene->getCameraRect().excluded(bounds()))
	{
		//
		// Eliminar si está fuera de la cámara
		//
		removable = true;
	}
	else
	{
		//
		// Cambiar frame
		//
		if(spriteClock.update(dt))
		{
			if(++spriteFrame >= sprite->count())
			{
				spriteFrame = 0;
			}
		}
		//
		// Aumentar aceleración
		//
		accel.x += (dirX*INCR_ACCELERATION);
		accel.y += (dirY*INCR_ACCELERATION);
		//
		// Controlar límites de velocidad y aceleración
		//
		if(vel.x > +MAX_VELOCITY)			vel.x = (+MAX_VELOCITY);
		else if(vel.x < -MAX_VELOCITY)		vel.x = (-MAX_VELOCITY);
		if(vel.y > +MAX_VELOCITY)			vel.y = (+MAX_VELOCITY);
		else if(vel.y < -MAX_VELOCITY)		vel.y = (-MAX_VELOCITY);
		if(accel.x > +MAX_ACCELERATION)		accel.x = (+MAX_ACCELERATION);
		if(accel.y > +MAX_ACCELERATION)		accel.y = (+MAX_ACCELERATION);
	}
}
void RocketLauncherBullet::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteFrame, spriteHints);
	if(Debug::showBulletRects)
	{
		gr->drawRect(bounds(), Debug::colorBulletRects);
	}
}
Rectanglef RocketLauncherBullet::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef RocketLauncherBullet::bounds(double px, double py) const
{
	return sprite->rectangle(px, py, spriteFrame, spriteHints);
}
void RocketLauncherBullet::hurt(HurtableRect* hr)
{
	removable = true;
	hr->hurt(2);
	scene->addEntity(new NormalExplosionS(scene, pos.x, pos.y));
}


