////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Frog
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/Frog.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/HeroBullet.h>

#include <mach/Math.h>
#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define JUMP_HEIGHT 42

Frog::Frog(Scene* s, double x, double y, int ___health, bool ___canJump) : Enemy(s, x, y)
, state(STATE_IDLE)
, health(___health)
, velocity()
, sheet(res.findSpriteSheet("Frog"))
, sprite(sheet->getSprite(getIdleSpriteName(health)))
, spriteIndex(0)
, spriteClock(0.4)
, canJump(___canJump)
{
}
Frog::~Frog()
{
}
void Frog::update(double dt)
{
	if(state == STATE_IDLE)
	{
		if(spriteClock.update(dt))
		{
			spriteIndex++;
			if(spriteIndex >= sprite->count())
				spriteIndex = 0;
		}
		if(canJump)
		{
			Vector2f p = scene->getHero()->getPosition();
			if(p.x < pos.x)
			{
				if(Math::abs(pos.x - p.x) < 60)
				{
					jump();
				}
			}
		}
	}
	else
	{
		Vector2f oldPosition = pos;
		Vector2f newVelocity = velocity;
		
		pos.x += velocity.x*dt;
		pos.y += velocity.y*dt + (Scene::GRAVITY*dt*dt)/2;
		velocity.y += Scene::GRAVITY*dt;
		
		if(state == STATE_JUMP)
		{
			unsigned int cflags = scene->checkCollision(
					this,
					pos,
					velocity,
					oldPosition,
					newVelocity,
					MAP_TERRAIN_SOLID);
			
			if(0 != (cflags & COLLISION_FLAG_BOTTOM))
			{
				state = STATE_IDLE;
				sprite = sheet->getSprite(getIdleSpriteName(health));
			}
		}
		else
		{
			if(pos.y-24 > scene->getCameraRect().getMaxY())
				removable = true;
		}
	}
	if(pos.x+12 < scene->getCameraRect().getMinX())
		removable = true;
}
void Frog::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteIndex, 0);
}
void Frog::collides(Entity* e)
{
	if(state != STATE_DEAD)
	{
		if(dynamic_cast<Hero*>(e))
		{
			collideWithHero((Hero*)e);
		}
		else if(dynamic_cast<HeroBullet*>(e))
		{
			if(health == 2)
			{
				health--;
				sprite = sheet->getSprite(getIdleSpriteName(health));
			}
			else
			{
				state = STATE_DEAD;
				velocity = Vector2f(0, -140);
				sprite = sheet->getSprite(getDeadSpriteName(health));
			}
			spriteIndex = 0;
			((HeroBullet*)e)->remove();
			
			Mixer::playChannel(res.findSound("KillEnemy"));
		}
	}
}
Rectanglef Frog::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef Frog::bounds(double px, double py) const
{
	if(state == STATE_JUMP)
		return Rectanglef(px-9, py-9, 18, 9);
	return Rectanglef(px-6, py-14, 12, 14);
}
Rectanglef Frog::getCollisionRectangle() const
{
	if(state == STATE_DEAD)
		return Rectanglef();
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return bounds();
}
void Frog::jump()
{
	state = STATE_JUMP;
	sprite = sheet->getSprite(getJumpSpriteName(health));
	spriteIndex = 0;
	velocity = Vector2f(-58, -Math::sqrt(JUMP_HEIGHT*2*Scene::GRAVITY));
}
