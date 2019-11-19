////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Pulposus
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/Pulposus.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/HeroBullet.h>

#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

Pulposus::Pulposus(Scene* s, double x, double y, int ___health) : Enemy(s, x, y)
, state(STATE_UP)
, health(___health)
, velocity()
, sheet(res.findSpriteSheet("Pulposus"))
, sprite(null)
, spriteIndex(0)
, spriteHints(0)
, spriteClock(0.14)
{
}
Pulposus::~Pulposus()
{
}
void Pulposus::update(double dt)
{
	pos += velocity*dt + (Scene::GRAVITY_ACCELERATION*dt*dt)/2;

	velocity += Scene::GRAVITY_ACCELERATION*dt;
	
	if(state == STATE_DEAD)
	{
		if(pos.y > scene->getCameraRect().getMaxY()+40)
			removable = true;
	}
	else
	{
		if(state == STATE_UP)
		{
			if(velocity.y > 0)
			{
				state = STATE_DOWN;
				if(health == 1)
					sprite = sheet->getSprite("Red-Down");
				else
					sprite = sheet->getSprite("Blue-Down");
				spriteIndex = 0;
			}
		}
		else
		{
			if(pos.y > scene->getCameraRect().getMaxY())
			{
				state = STATE_UP;
				if(health == 1)
					sprite = sheet->getSprite("Red-Up");
				else
					sprite = sheet->getSprite("Blue-Up");
				spriteIndex = 0;
				velocity.y = -430;
			}
		}
		if(spriteClock.update(dt))
		{
			spriteIndex++;
			if(spriteIndex >= sprite->count())
				spriteIndex = 0;
		}
	}
	if(pos.x+6 < scene->getCameraRect().getMinX())
		removable = true;
}
void Pulposus::render(Graphics* gr)
{
	if(sprite != null)
		sprite->render(gr, pos.x, pos.y, spriteIndex, spriteHints);
}
void Pulposus::collides(Entity* e)
{
	if(dynamic_cast<Hero*>(e))
	{
		collideWithHero((Hero*)e);
	}
	else if(dynamic_cast<HeroBullet*>(e))
	{
		health--;
		scene->getHero()->addScore(100, 0);
		if(health == 0)
		{
			state = STATE_DEAD;
			sprite = sheet->getSprite("Red-Up");
			spriteIndex = 0;
			spriteHints = Sprite::FLIP_Y;
			if(((HeroBullet*)e)->getVelocity().x > 0)
				velocity = Vector2f(+70, -80);
			else
				velocity = Vector2f(-70, -80);
		}
		else
		{
			if(state == STATE_UP)
				sprite = sheet->getSprite("Red-Up");
			else
				sprite = sheet->getSprite("Red-Down");
		}
		((HeroBullet*)e)->remove();
		
		Mixer::playChannel(res.findSound("KillEnemy"));
	}
}
Rectanglef Pulposus::getCollisionRectangle() const
{
	if(state == STATE_DEAD)
		return Rectanglef();
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return Rectanglef(pos.x - 6, pos.y, 12, 20);
}
