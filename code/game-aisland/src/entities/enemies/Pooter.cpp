////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Pooter
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/Pooter.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/HeroBullet.h>

#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

Pooter::Pooter(Scene* s, double x, double y) : Enemy(s, x, y)
, alive(true)
, velocity(-40, 0)
, sheet(res.findSpriteSheet("Pooter"))
, sprite(sheet->getSprite("Walk"))
, spriteIndex(0)
, spriteClock(0.3)
{
}
Pooter::~Pooter()
{
}
void Pooter::update(double dt)
{
	if(spriteClock.update(dt))
	{
		spriteIndex++;
		if(spriteIndex >= sprite->count())
			spriteIndex = 0;
	}
	if(alive)
	{
		pos.x += velocity.x*dt;
	}
	else
	{
		pos += velocity*dt + (Scene::GRAVITY_ACCELERATION*dt*dt)/2;
		velocity += Scene::GRAVITY_ACCELERATION*dt;
		
		// ...
		if(pos.y-26 > scene->getCameraRect().getMaxY())
			removable = true;
	}
	if(pos.x+12 < scene->getCameraRect().getMinX())
		removable = true;
}
void Pooter::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteIndex, 0);
}
void Pooter::collides(Entity* e)
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
}
Rectanglef Pooter::getCollisionRectangle() const
{
	if(!alive)
		return Rectanglef();
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return Rectanglef(pos.x - 6, pos.y - 22, 12, 22);
}
