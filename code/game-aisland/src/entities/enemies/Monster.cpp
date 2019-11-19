////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Monster
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/Monster.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/HeroBulletAx.h>
#include <src/entities/hero/HeroBulletFireball.h>
#include <src/entities/enemies/MonsterBullet.h>
#include <src/entities/effects/ScoreEffect.h>
#include <src/entities/effects/SplashEffect.h>

#include <mach/Mixer.h>
#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define DISTANCE_X 60

Monster::Monster(Scene* s, double x, double y, int ___type) : Enemy(s, x, y)
, type(___type)
, state(STATE_WALK)
, alive(true)
, health(20)
, sheet(res.findSpriteSheet("Monster"))
, bodySprite(sheet->getSprite("Walk"))
, bodySpriteIndex(0)
, headSprite(sheet->getSprite("Head"))
, headSpriteIndex(0)
, bulletSprite(sheet->getSprite("Bullet"))
, bulletSpriteIndex(0)
, startX(x)
, walkDir(-1)
, walkClock(0.4)
, attackClock(0.2)
, bulletClock(0.04)
, nextAttackClock(0.7)
, headDamagedClock(0.15)
{
}
Monster::~Monster()
{
}
void Monster::update(double dt)
{
	if(alive)
	{
		if(headSpriteIndex == 1)
		{
			if(headDamagedClock.update(dt))
				headSpriteIndex = 0;
		}
		if(state == STATE_WALK)
		{
			if(walkClock.update(dt))
			{
				if(++bodySpriteIndex >= bodySprite->count())
				{
					bodySpriteIndex = 0;
				}
				if(walkDir == -1)
				{
					pos.x -= 5;
					if(pos.x <= startX-DISTANCE_X)
					{
						pos.x = startX-DISTANCE_X;
						walkDir = +1;
					}
				}
				else
				{
					pos.x += 5;
					if(pos.x >= startX)
					{
						pos.x = startX;
						walkDir = -1;
					}
				}
			}
			if(nextAttackClock.update(dt))
			{
				state = STATE_ATTACK;
				bodySprite = sheet->getSprite("Attack");
				bodySpriteIndex = 0;
				attackClock.reset(1);
			}
		}
		else if(state == STATE_ATTACK)
		{
			if(attackClock.update(dt))
			{
				if(++bodySpriteIndex == 1)
				{
					attackClock.reset(0.3);
					scene->addEntity(new MonsterBullet(scene,
						pos.x + 22,
						pos.y - 48,
						bulletSprite));
				}
				else
				{
					state = STATE_WALK;
					bodySprite = sheet->getSprite("Walk");
					bodySpriteIndex = 0;
				}
			}
			if(bulletClock.update(dt))
			{
				bulletSpriteIndex = !bulletSpriteIndex;
			}
		}
	}
	else
	{
		if(state == STATE_FALLING_HEAD)
		{
			headPosition += headVelocity*dt + (Scene::GRAVITY_ACCELERATION*dt*dt)/2;
			headVelocity += Scene::GRAVITY_ACCELERATION*dt;

			if(headPosition.y-100 > scene->getCameraRect().getMaxY())
			{
				state = STATE_GO_OUT;
				double x = pos.x;
				double y = pos.y - 54;
				scene->getHero()->addScore(5000, 0);
				scene->addEntity(new ScoreEffect(scene, x, y, 5000));
				scene->addEntity(new SplashEffect(scene, x, y));
			}
		}
		else if(state == STATE_GO_OUT)
		{
			pos += Vector2f(220, -200)*dt + (Scene::GRAVITY_ACCELERATION*dt*dt)/2;
			
			if(pos.y < -100)
			{
				Hero* h = scene->getHero();
				if(!h->isWinner())
				{
					h->win();
					Mixer::playMusic(res.findMusic("AreaCompleted"));
				}
			}
		}
	}
}
void Monster::render(Graphics* gr)
{
	int dx = (state == STATE_ATTACK && bodySpriteIndex == 0) ? 4 : 0;
	
	bodySprite->render(gr, pos.x, pos.y, bodySpriteIndex, 0);
	if(alive)
	{
		headSprite->render(gr, pos.x + dx, pos.y, (type*2)+headSpriteIndex, 0);
	}
	else
	{
		headSprite->render(gr, headPosition.x + dx, headPosition.y, (type*2)+1, 0);
	}
	if(state == STATE_ATTACK)
	{
		if(bodySpriteIndex == 0)
		{
			bulletSprite->render(gr, pos.x + 22, pos.y - 48, bulletSpriteIndex, 0);
		}
	}
	if(Debug::showCollisionRect)
	{
		gr->drawRect(bounds(), Color(255,0,0));
		
		gr->drawRect(headRect(), Color(255,0,0));
	}
}
void Monster::collides(Entity* e)
{
	if(dynamic_cast<Hero*>(e))
	{
		((Hero*)e)->dead();
	}
	else if(dynamic_cast<HeroBulletAx*>(e))
	{
		if(headRect().intersects(e->getCollisionRectangle()))
		{
			health -= 1;
			((HeroBulletAx*)e)->remove();
			
			headSpriteIndex = 1;
		}
		else if(bodySprite->rectangle(pos.x, pos.y, 0, 0).intersects(e->getCollisionRectangle()))
		{
			((HeroBulletAx*)e)->remove();
		}
	}
	else if(dynamic_cast<HeroBulletFireball*>(e))
	{
		if(headRect().intersects(e->getCollisionRectangle()))
		{
			health -= 2;
			((HeroBulletFireball*)e)->remove();
			
			headSpriteIndex = 1;
		}
		else if(bodySprite->rectangle(pos.x, pos.y, 0, 0).intersects(e->getCollisionRectangle()))
		{
			((HeroBulletFireball*)e)->remove();
		}
	}
	if(health <= 0)
	{
		alive = false;
		health = 0;
		state = STATE_FALLING_HEAD;
		
		headPosition = pos;
		headVelocity = Vector2f(-120, -80);
	}
}
Rectanglef Monster::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef Monster::bounds(double px, double py) const
{
	return Rectanglef(px - 14, py - 78, 28, 78);
}
Rectanglef Monster::getCollisionRectangle() const
{
	if(!alive)
		return Rectanglef();
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return bounds();
}
Rectanglef Monster::headRect() const
{
	return headSprite->rectangle(pos.x + ((state == STATE_ATTACK && bodySpriteIndex == 0) ? 4 : 0), pos.y, 0, 0);
}
