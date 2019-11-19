////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CobraBullet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/CobraBullet.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define VELOCITY_Y 14

CobraBullet::CobraBullet(Scene* s, double x, double y) : Enemy(s, x, y)
, dir(1)
, minY(y - 4)
, maxY(y + 4)
, sheet(res.findSpriteSheet("CobraBullet"))
, sprite(sheet->getSprite("Idle"))
, spriteIndex(0)
, spriteClock(0.3)
{
}
CobraBullet::~CobraBullet()
{
}
void CobraBullet::update(double dt)
{
	if(spriteClock.update(dt))
	{
		spriteIndex++;
		if(spriteIndex >= sprite->count())
			spriteIndex = 0;
	}
	pos.x -= 30*dt;
	if(dir == 1)
	{
		pos.y += VELOCITY_Y*dt;
		
		if(pos.y >= maxY)
		{
			dir = -1;
			pos.y = maxY;
		}
	}
	else
	{
		pos.y -= VELOCITY_Y*dt;
		
		if(pos.y <= minY)
		{
			dir = +1;
			pos.y = minY;
		}
	}
	if(pos.x+12 < scene->getCameraRect().getMinX())
		removable = true;
}
void CobraBullet::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteIndex, 0);
}
void CobraBullet::collides(Entity* e)
{
	if(dynamic_cast<Hero*>(e))
	{
		collideWithHero((Hero*)e);
	}
}
Rectanglef CobraBullet::getCollisionRectangle() const
{
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return Rectanglef(pos.x - 7, pos.y - 3, 10, 6);
}
