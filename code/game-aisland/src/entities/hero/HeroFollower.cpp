////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroFollower
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/HeroFollower.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>

#include <mach/Math.h>

HeroFollower::HeroFollower(Scene* s, double x, double y)
: Entity(s, x, y)
, hero(scene->getHero())
, state(STATE_IDLE)
, velocity(100, -80)
, dy(0)
, dir(1)
, clock(0.03)
, readyX(false)
, readyY(false)
{
}
HeroFollower::~HeroFollower()
{
}
void HeroFollower::update(double dt)
{
	if(state == STATE_IDLE)
	{
		double hx = hero->getPosition().x-8;
		double hy = hero->getPosition().y-32;

		if(!readyX)
		{
			if(pos.x > hx) pos.x -= dt*80;
			else if(pos.x < hx) pos.x += dt*80;
			if(Math::abs(hx-pos.x) <= 2)
				readyX = true;
		}
		else
		{
			pos.x = hx;
		}
		if(!readyY)
		{
			if(pos.y > hy) pos.y -= dt*80;
			else if(pos.y < hy) pos.y += dt*80;
			if(Math::abs(hy-pos.y) <= 2) readyY = true;
		}
		else
		{
			pos.y = hy;
		}
	}
	else if(state == STATE_LEAVE)
	{
		pos.x += velocity.x*dt;
		pos.y += velocity.y*dt;
		
		if(pos.y < scene->getCameraRect().getMinY())
		{
			removable = true;
		}
	}
	if(clock.update(dt))
	{
		if(dir == 1)
		{
			dy++;
			if(dy > +1)
			{
				dy--;
				dir = -1;
			}
		}
		else
		{
			dy--;
			if(dy < -1)
			{
				dy++;
				dir = +1;
			}
		}
	}
}
void HeroFollower::leave()
{
	state = STATE_LEAVE;
}
