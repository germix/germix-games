////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Cobra
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/Cobra.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/HeroBullet.h>
#include <src/entities/enemies/CobraBullet.h>

#include <mach/Mixer.h>
#include <mach/Graphics.h>

Cobra::Cobra(Scene* s, double x, double y) : Enemy(s, x, y)
, alive(true)
, texture(res.findTexture("Cobra"))
, velocityY(0)
, firstTime(true)
, attackClock(2)
{
}
Cobra::~Cobra()
{
}
void Cobra::update(double dt)
{
	if(!alive)
	{
		pos.y += velocityY*dt + (Scene::GRAVITY*dt*dt)/2;
		velocityY += Scene::GRAVITY*dt;
		
		if(pos.y-24 > scene->getCameraRect().getMaxY())
			removable = true;
	}
	else
	{
		if(firstTime)
		{
			if(attackClock.update(dt))
			{
				scene->addEntity(new CobraBullet(scene, pos.x - 8, pos.y - 12));
				firstTime = false;
				attackClock.reset(5);
			}
		}
		else
		{
			if(attackClock.update(dt))
			{
				scene->addEntity(new CobraBullet(scene, pos.x - 8, pos.y - 12));
			}
		}
	}
	if(pos.x+16 < scene->getCameraRect().getMinX())
	{
		removable = true;
	}
}
void Cobra::render(Graphics* gr)
{
	gr->drawTexture(texture, int(pos.x - 8), int(pos.y - 23));
}
void Cobra::collides(Entity* e)
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
			velocityY = -200;
			((HeroBullet*)e)->remove();
			
			Mixer::playChannel(res.findSound("KillEnemy"));
		}
	}
}
Rectanglef Cobra::getCollisionRectangle() const
{
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return Rectanglef(pos.x - 7, pos.y - 22, 14, 22);
}

