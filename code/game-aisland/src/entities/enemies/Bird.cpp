////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bird
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/Bird.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/HeroBullet.h>

#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

Bird::Bird(Scene* s, double x, double y, const String& eggEntity) : Enemy(s, x, y, eggEntity)
, dir(1)
, min(y-24)
, max(y+24)
, vel(60)
, alive(true)
, velocity()
, sheet(res.findSpriteSheet("Bird"))
, sprite(sheet->getSprite("Fly"))
, spriteHints(0)
, spriteIndex(0)
, spriteClock(0.2)
{
}
Bird::~Bird()
{
}
void Bird::update(double dt)
{
	if(alive)
	{
		if(spriteClock.update(dt))
		{
			if(++spriteIndex >= sprite->count())
			{
				spriteIndex = 0;
			}
		}
		if(pos.x + 32 <  scene->getCameraRect().getMinX())
		{
			removable = true;
		}
		if(dir == 1)
		{
			pos.y += vel*dt;
			
			if(pos.y >= max)
			{
				dir = -1;
				pos.y = max;
			}
		}
		else
		{
			pos.y -= vel*dt;
			
			if(pos.y <= min)
			{
				dir = +1;
				pos.y = min;
			}
		}
		pos.x -= 30*dt;
	}
	else
	{
		pos.x += velocity.x*dt;
		pos.y += velocity.y*dt + (Scene::GRAVITY*dt*dt)/2;
		velocity.y += Scene::GRAVITY*dt;
		
		if(pos.y - 32 >  scene->getCameraRect().getMaxY())
		{
			removable = true;
		}
	}
}
void Bird::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteIndex, spriteHints);
}
void Bird::collides(Entity* e)
{
	if(alive)
	{
		if(dynamic_cast<Hero*>(e))
		{
			collideWithHero((Hero*)e);
		}
		else if(dynamic_cast<HeroBullet*>(e))
		{
			alive = false;
			spriteHints = Sprite::FLIP_X | Sprite::FLIP_Y;
			if(((HeroBullet*)e)->getVelocity().x > 0)
				velocity = Vector2f(+80, 0);
			else
				velocity = Vector2f(-80, 0);
			
			((HeroBullet*)e)->remove();
			
			Mixer::playChannel(res.findSound("KillEnemy"));
		}
	}
}
Rectanglef Bird::getCollisionRectangle() const
{
	if(!alive)
		return Rectanglef();
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return sprite->rectangle(pos.x, pos.y, spriteIndex, spriteHints);
}
