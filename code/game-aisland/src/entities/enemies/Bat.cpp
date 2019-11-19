////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bat
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/Bat.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/HeroBullet.h>

#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define VELOCITY_X		30
#define VELOCITY_Y		130

Bat::Bat(Scene* s, double x, double y, int baseY) : Enemy(s, x, y)
, state(STATE_INACTIVE)
, dir(1)
, minY(baseY - 10)
, maxY(baseY + 10)
, velocity()
, sheet(res.findSpriteSheet("Bat"))
, sprite(sheet->getSprite("Idle"))
, spriteIndex(0)
, spriteClock(0.2)
{
}
Bat::~Bat()
{
}
void Bat::update(double dt)
{
	if(state == STATE_INACTIVE)
	{
		if(pos.x - scene->getHero()->getPosition().x < 130)
		{
			state = STATE_FLYING;
			sprite = sheet->getSprite("Fly");
		}
	}
	else if(state == STATE_DEAD)
	{
		pos.x += velocity.x*dt;
		pos.y += velocity.y*dt + (Scene::GRAVITY*dt*dt)/2;
		
		velocity.y += Scene::GRAVITY*dt;
		
		if(pos.y - 22 > scene->getCameraRect().getMaxY())
		{
			removable = true;
		}
	}
	else
	{
		if(spriteClock.update(dt))
		{
			spriteIndex++;
			if(spriteIndex >= sprite->count())
				spriteIndex = 0;
		}
		pos.x -= VELOCITY_X*dt;
		
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
	}
}
void Bat::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteIndex, 0);
}
void Bat::collides(Entity* e)
{
	if(dynamic_cast<Hero*>(e))
	{
		collideWithHero((Hero*)e);
	}
	else if(dynamic_cast<HeroBullet*>(e))
	{
		state = STATE_DEAD;
		sprite = sheet->getSprite("Dead");
		spriteIndex = 0;
		if(((HeroBullet*)e)->getVelocity().x > 0)
			velocity = Vector2f(+70, -80);
		else
			velocity = Vector2f(-70, -80);
		((HeroBullet*)e)->remove();
		
		Mixer::playChannel(res.findSound("KillEnemy"));
	}
}
Rectanglef Bat::getCollisionRectangle() const
{
	if(state == STATE_DEAD)
		return Rectanglef();
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return Rectanglef(pos.x - 6, pos.y - 14, 12, 14);
}

