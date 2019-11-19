////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusBox | Caja contenedora de bonus
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/BonusBox.h>
#include <src/Debug.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/bonus/Bonus.h>
#include <src/entities/bonus/BonusFactory.h>

#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

BonusBox::BonusBox(Scene* scene, double x, double y, const char* bonus) : Entity(scene, x, y)
, vel()
, accel(0, GRAVITY_CONSTANT*GRAVITY_DOWN)
, onGround(false)
, sprite(null)
, spriteFrame(0)
, spriteClock(0)
, destroyed(false)
, droppableBonus(bonus)
{
	sprite = res.findSpriteSheet("BonusBox")->getSprite();
}
BonusBox::~BonusBox()
{
}
void BonusBox::update(double dt)
{
	if(!onGround)
	{
		CollisionInfo ci = scene->moveEntity(this, dt, pos, vel, accel, onGround, MAP_TERRAIN_SOLID|MAP_TERRAIN_TOPDOWN);
		
		onGround = (ci.flags & COLLISION_FLAG_BOTTOM) != 0;
	}
	if(destroyed)
	{
		if(spriteClock.update(dt))
		{
			spriteFrame++;
			if(spriteFrame >= sprite->count())
			{
				removable = true;
			}
		}
	}
}
void BonusBox::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteFrame, 0);
	if(Debug::showBonusRects)
	{
		gr->drawRect(bounds(), Debug::colorBonusRects);
	}
}
Rectanglef BonusBox::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef BonusBox::bounds(double px, double py) const
{
	return sprite->rectangle("Collider", px, py, spriteFrame, 0);
}
void BonusBox::knifeHurt(int damage)
{
	destroyMe();
}
bool BonusBox::isKnifeHurtable() const
{
	return (destroyed) ? false : true;
}
void BonusBox::hurt(int damage)
{
	destroyMe();
}
bool BonusBox::isHurtable() const
{
	return (destroyed) ? false : true;
}
Rectanglef BonusBox::hurtableRect() const
{
	return bounds();
}
void BonusBox::destroyMe()
{
	if(!destroyed)
	{
		destroyed = true;
		scene->addEntityBackOfOther(this, BonusFactory::create(scene, pos.x, pos.y-16, droppableBonus.c_str()));
	}
}
