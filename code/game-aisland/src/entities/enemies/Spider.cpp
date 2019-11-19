////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Spider
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/Spider.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/HeroBullet.h>

#include <mach/Mixer.h>
#include <mach/Graphics.h>

Spider::Spider(Scene* s, double x, double y, int ___min, int ___max) : Enemy(s, x, y)
, dir(1)
, min(___min)
, max(___max)
, mode((___min == ___max) ? MODE_FIXED : MODE_MOVABLE)
, alive(true)
, texture(res.findTexture("Spider"))
, velocity(0, 30)
{
}
Spider::~Spider()
{
}
void Spider::update(double dt)
{
	if(alive)
	{
		if(mode == MODE_MOVABLE)
		{
			if(dir == 1)
			{
				pos.y += velocity.y*dt;
				if(pos.y >= max)
				{
					dir = -1;
					pos.y = max;
				}
			}
			else
			{
				pos.y -= velocity.y*dt;
				if(pos.y <= min)
				{
					dir = +1;
					pos.y = min;
				}
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
void Spider::render(Graphics* gr)
{
	gr->drawTexture(texture, int(pos.x - 7), int(pos.y - 15));
}
void Spider::collides(Entity* e)
{
	if(dynamic_cast<Hero*>(e))
	{
		collideWithHero((Hero*)e);
	}
	else if(dynamic_cast<HeroBullet*>(e))
	{
		alive = false;
		if(((HeroBullet*)e)->getVelocity().x > 0)
			velocity = Vector2f(+70, -80);
		else
			velocity = Vector2f(-70, -80);
		((HeroBullet*)e)->remove();

		Mixer::playChannel(res.findSound("KillEnemy"));
	}
}
Rectanglef Spider::getCollisionRectangle() const
{
	if(!alive)
		return Rectanglef();
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return Rectanglef(pos.x - 7, pos.y - 15, 14, 15);
}


