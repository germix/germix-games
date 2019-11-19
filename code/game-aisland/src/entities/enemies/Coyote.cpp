////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Coyote
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/Coyote.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/HeroBullet.h>
#include <src/entities/bonus/Bonus_Gamepad.h>

#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

Coyote::Coyote(Scene* s, double x, double y) : Enemy(s, x, y)
, state(STATE_INACTIVE)
, clock(0.1)
, health(2)
, velocity(180)
, sheet(res.findSpriteSheet("Coyote"))
, sprite(sheet->getSprite("Walk1"))
, spriteIndex(0)
{
}
Coyote::~Coyote()
{
}
void Coyote::update(double dt)
{
	switch(state)
	{
		case STATE_INACTIVE:
			if(pos.x+24 < scene->getCameraRect().getMinX())
			{
				state = STATE_WALKING;
			}
			break;
		case STATE_WALKING:
			pos.x += velocity*dt;
			if(clock.update(dt))
			{
				spriteIndex++;
				if(spriteIndex >= sprite->count())
					spriteIndex = 0;
			}
			if(pos.x-12 > scene->getCameraRect().getMaxX())
				removable = true;
			break;
		case STATE_STOPPED:
			if(clock.update(dt))
			{
				state = STATE_WALKING;
				clock.reset(0.1);
			}
			break;
		case STATE_DEAD:
			{
				pos.y += velocity*dt + (Scene::GRAVITY*dt*dt)/2;
				velocity += Scene::GRAVITY*dt;
				
				if(pos.y > scene->getCameraRect().getMaxY())
					removable = true;
			}
			break;
	}
}
void Coyote::render(Graphics* gr)
{
	if(state != STATE_INACTIVE)
		sprite->render(gr, pos.x, pos.y, spriteIndex, (health == 0) ? (Sprite::FLIP_X | Sprite::FLIP_Y) : 0);
}
void Coyote::collides(Entity* e)
{
	if(dynamic_cast<Hero*>(e))
	{
		collideWithHero((Hero*)e);
	}
	else if(dynamic_cast<HeroBullet*>(e))
	{
		health--;
		scene->getHero()->addScore(500, 0);
		if(health == 0)
		{
			state = STATE_DEAD;
			pos.y -= 42;
			velocity = -200;
			if(scene->getHero()->getPosition().x < pos.x)
			{
				scene->addEntity(
						new Bonus_Gamepad(
								scene,
								scene->getHero()->getPosition().x + 80,
								scene->getHero()->getPosition().y - 18));
			}
		}
		else
		{
			state = STATE_STOPPED;
			clock.reset(0.6);
			sprite = sheet->getSprite("Walk2");
		}
		((HeroBullet*)e)->remove();
		Mixer::playChannel(res.findSound("KillEnemy"));
	}
}
Rectanglef Coyote::getCollisionRectangle() const
{
	if(health == 0 || state == STATE_INACTIVE)
		return Rectanglef();
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return Rectanglef(pos.x - 6, pos.y - 22, 16, 22);
}
