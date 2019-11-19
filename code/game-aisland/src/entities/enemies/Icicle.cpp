////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Icicle
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/Icicle.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/HeroBullet.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

Icicle::Icicle(Scene* s, double x, double y) : Enemy(s, x, y)
, state(STATE_INACTIVE)
, sheet(res.findSpriteSheet("Icicle"))
, sprite(sheet->getSprite("Idle"))
, velocity()
, crashClock(0.5)
{
}
Icicle::~Icicle()
{
}
void Icicle::update(double dt)
{
	if(state == STATE_INACTIVE)
	{
		if(pos.x - scene->getHero()->getPosition().x < 60)
		{
			state = STATE_FALLING;
		}
	}
	else if(state == STATE_FALLING)
	{
		Vector2f oldPosition = pos;
		Vector2f oldVelocity = velocity;
		
#if 0
		pos.y += velocity.y*dt + (Scene::GRAVITY*dt*dt)/2;
		velocity.y += Scene::GRAVITY*dt;
#else
		pos.y += velocity.y*dt + ((Scene::GRAVITY/2)*dt*dt)/2;
		velocity.y += (Scene::GRAVITY/2)*dt;
#endif
		
		unsigned int cflags = scene->checkCollision(
				this,
				pos,
				velocity,
				oldPosition,
				oldVelocity,
				MAP_TERRAIN_SOLID);
		
		if(0 != (cflags & COLLISION_FLAG_BOTTOM))
		{
			state = STATE_CRASH;
			sprite = sheet->getSprite("Crash");
		}
	}
	else if(state == STATE_CRASH)
	{
		if(crashClock.update(dt))
			removable = true;
	}
}
void Icicle::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, 0, 0);
}
void Icicle::collides(Entity* e)
{
	if(dynamic_cast<Hero*>(e))
	{
		collideWithHero((Hero*)e);
	}
	else if(dynamic_cast<HeroBullet*>(e))
	{
		state = STATE_CRASH;
		sprite = sheet->getSprite("Crash");
		((HeroBullet*)e)->remove();
	}
}
Rectanglef Icicle::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef Icicle::bounds(double px, double py) const
{
	return Rectanglef(px - 7, py - 24, 14, 24);
}
Rectanglef Icicle::getCollisionRectangle() const
{
	if(state == STATE_CRASH)
		return Rectanglef();
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return bounds();
}
