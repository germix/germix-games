////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SoldierBullet | Bala del soldado
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/soldier/SoldierBullet.h>
#include <src/Debug.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>

#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

SoldierBullet::SoldierBullet(Scene* scene, double px, double py, int dirX) : EnemyProjectile(scene, px, py)
, sprite(null)
, spriteFrame(0)
, spriteClock(0.08)
, velocityX(dirX * 100)
{
	sprite = res.findSpriteSheet("SoldierBullet")->getSprite();
}
SoldierBullet::~SoldierBullet()
{
}
void SoldierBullet::update(double dt)
{
	pos.x += (velocityX*dt);
	if(scene->getCameraRect().excluded(bounds()))
	{
		removable = true;
	}
	else
	{
		if(spriteClock.update(dt))
		{
			if(++spriteFrame >= sprite->count())
			{
				spriteFrame = 0;
			}
		}
	}
}
void SoldierBullet::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteFrame, spriteFrame);
	if(Debug::showBulletRects)
	{
		gr->drawRect(bounds(), Debug::colorBulletRects);
	}
}
Rectanglef SoldierBullet::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef SoldierBullet::bounds(double px, double py) const
{
	return Rectanglef(pos.x-4, pos.y-4, 8, 8);
}
void SoldierBullet::collide(Entity* other)
{
	if(dynamic_cast<Hero*>(other))
	{
		removable = true;
		((Hero*)other)->hurt();
	}
}
Rectanglef SoldierBullet::collisionRect() const
{
	return bounds();
}
