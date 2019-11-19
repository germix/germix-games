////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ShotGunExplosion | Explosión del ShotGun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/weapons/ShotGunExplosion.h>
#include <src/Debug.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/___/HurtableRect.h>

#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define SHOTGUN_DAMAGE 5

ShotGunExplosion::ShotGunExplosion(Scene* scene, double px, double py, int shotAngle, int lookX) : Entity(scene, px, py)
, sprite(null)
, spriteHints(0)
, spriteFrame(0)
, spriteClock(0.024)
, firstTime(true)
{
	if(shotAngle == 0)
	{
		sprite = res.findSpriteSheet("Bullet.S")->getSprite("Horz");
		if(lookX == -1)
			spriteHints |= Sprite::FLIP_X;
	}
	else
	{
		sprite = res.findSpriteSheet("Bullet.S")->getSprite("Vert");
		if(lookX == -1)
			spriteHints |= Sprite::FLIP_X;
		if(shotAngle == -90)
			spriteHints |= Sprite::FLIP_Y;
	}
}
ShotGunExplosion::~ShotGunExplosion()
{
}
void ShotGunExplosion::update(double dt)
{
	if(spriteClock.update(dt))
	{
		if(++spriteFrame >= sprite->count())
		{
			spriteFrame = 0;
			removable = true;
		}
	}
	if(firstTime)
	{
		std::vector<HurtableRect*> rects = scene->getHurtableRectanglesInArea(bounds());
		for(unsigned int i = 0; i < rects.size(); i++)
		{
			rects[i]->hurt(SHOTGUN_DAMAGE);
		}
		firstTime = false;
	}
}
void ShotGunExplosion::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteFrame, spriteHints);
	if(Debug::showBulletRects)
	{
		gr->drawRect(bounds(), Debug::colorBulletRects);
	}
}
Rectanglef ShotGunExplosion::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef ShotGunExplosion::bounds(double px, double py) const
{
	return sprite->rectangle(px, py, spriteFrame, spriteHints).inflate(-8);
}


