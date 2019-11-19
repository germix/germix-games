////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IronNokanaRocket | Cohete del IronNokana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/nokana/IronNokanaRocket.h>
#include <src/Debug.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/routes/Route.h>
#include <src/routes/RouteCoordinate.h>
#include <src/entities/effects/NormalExplosionS.h>

#include <mach/Math.h>
#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define ROCKET_VELOCITY				140.0
#define ANIMATION_TIME_STARTING		0.04
#define ANIMATION_TIME_SUBSPRITE	0.08

IronNokanaRocket::IronNokanaRocket(Scene* scene, double x, double y, Route* r) : EnemyProjectile(scene, x, y)
, state(STATE_STARTING)
, sprite(null)
, spriteFrame(0)
, spriteClock(ANIMATION_TIME_STARTING)
, route(r)
, oldPos(x, y)
, basePos(x, y)
, travaled(0)
, subSpriteFrame(0)
{
	sprite = res.findSpriteSheet("IronNokanaRocket")->getSprite("Starting");
}
IronNokanaRocket::~IronNokanaRocket()
{
}
void IronNokanaRocket::update(double dt)
{
	switch(state)
	{
		case STATE_STARTING:
			if(spriteClock.update(dt))
			{
				if(++spriteFrame >= sprite->count())
				{
					state = STATE_FLYING;
					sprite = res.findSpriteSheet("IronNokanaRocket")->getSprite("Flying");
					spriteFrame = 16*2;
					spriteClock.reset(ANIMATION_TIME_SUBSPRITE);
				}
			}
			break;
		case STATE_FLYING:
			travaled += ROCKET_VELOCITY*dt;
			{
				RouteCoordinate rc;
				
				route->getCoordinateFromTraveled(travaled, &rc);
				
				oldPos = pos;
				pos.x = rc.x+basePos.x;
				pos.y = rc.y+basePos.y;
				//
				// Calcular frame
				//
				if(Math::abs(pos.x-oldPos.x) > 0)
				{
					double angle = Math::atan2(pos.y-oldPos.y, pos.x-oldPos.x);
					
					double degrees = angle * (180.0/Math::PI);
					if(degrees < 0.0)
						degrees = 360.0 + degrees;
					
					spriteFrame = Math::min(31, (int)Math::round((degrees/360.0)*32.0));
					
					if(spriteClock.update(dt))
					{
						subSpriteFrame = ((++subSpriteFrame)&1);
					}
					spriteFrame *= 2;
					spriteFrame += subSpriteFrame;
				}
			}
			break;
	}
}
void IronNokanaRocket::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteFrame, 0);

	if(Debug::showBulletRects)
	{
		gr->drawRect(bounds(), Debug::colorBulletRects);
	}
}
Rectanglef IronNokanaRocket::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef IronNokanaRocket::bounds(double px, double py) const
{
	return Rectanglef(px-6, py-6, 12, 12);
}
void IronNokanaRocket::hurt(int damage)
{
	removable = true;
	scene->getHero()->addScore(10);
	scene->addEntity(new NormalExplosionS(scene, pos.x, pos.y));
}
bool IronNokanaRocket::isHurtable() const
{
	return true;
}
Rectanglef IronNokanaRocket::hurtableRect() const
{
	return bounds();
}
void IronNokanaRocket::collide(Entity* other)
{
	if(dynamic_cast<Hero*>(other))
	{
		removable = true;
		((Hero*)other)->hurt();
		scene->addEntity(new NormalExplosionS(scene, pos.x, pos.y));
	}
}
Rectanglef IronNokanaRocket::collisionRect() const
{
	return bounds();
}
