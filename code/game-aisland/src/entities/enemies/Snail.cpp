////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Snail
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/Snail.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/HeroBullet.h>

#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

Snail::Snail(Scene* s, double x, double y) : Enemy(s, x, y)
, alive(true)
, velocity()
, sheet(res.findSpriteSheet("Snail"))
, sprite(sheet->getSprite("Idle"))
, spriteIndex(0)
, spriteClock(1)
{
}
Snail::~Snail()
{
}
void Snail::update(double dt)
{
	if(alive)
	{
		if(spriteClock.update(dt))
		{
			if(++spriteIndex >= sprite->count())
			{
				pos.x--;
				spriteIndex = 0;
			}
		}
	}
	else
	{
		pos += velocity*dt + (Scene::GRAVITY_ACCELERATION*dt*dt)/2;
		velocity += Scene::GRAVITY_ACCELERATION*dt;
		
		if(pos.y - 22 > scene->getCameraRect().getMaxY())
		{
			removable = true;
		}
	}
}
void Snail::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteIndex, 0);
}
void Snail::collides(Entity* e)
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
			if(((HeroBullet*)e)->getVelocity().x > 0)
				velocity = Vector2f(+100, -130);
			else
				velocity = Vector2f(-100, -130);
			((HeroBullet*)e)->remove();
			
			sprite = sheet->getSprite("Dead");
			spriteIndex = 0;
			
			Mixer::playChannel(res.findSound("KillEnemy"));
		}
	}
}
Rectanglef Snail::getCollisionRectangle() const
{
	if(!alive)
		return Rectanglef();
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return Rectanglef(pos.x - 10, pos.y - 20, 20, 20);
}
