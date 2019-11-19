////////////////////////////////////////////////////////////////////////////////////////////////////
//
// JumpSpring
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/JumpSpring.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/entities/hero/Hero.h>
#include <src/EntityParameters.h>

#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

JumpSpring::JumpSpring(Scene* s, double x, double y, int initialState) : Platform(s, x, y, EntityParameters(), 0)
, jump(true)
, state(initialState)
, sprite(res.findSpriteSheet("JumpSpring")->getSprite("None"))
{
}
JumpSpring::~JumpSpring()
{
}
void JumpSpring::update(double dt)
{
	if(hero != null)
	{
		if(state == STATE_DOWN)
		{
			hero->setPositionY(pos.y - 14);
		}
		else
		{
			if(jump)
			{
				hero->superJump();
				releaseHero();
				jump = false;
			}
		}
	}
}
void JumpSpring::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, state, 0);

	if(Debug::showCollisionRect)
	{
		gr->drawRect(sprite->rectangle(pos.x, pos.y, state, 0), Color(255,0,0));
	}
}
Rectanglef JumpSpring::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef JumpSpring::bounds(double px, double py) const
{
	return sprite->rectangle(px, py, state, 0);
}
Rectanglef JumpSpring::getCollisionRectangle() const
{
	return bounds();
}
void JumpSpring::setHero(Hero* h)
{
	if(hero == null)
	{
		if(state == STATE_DOWN)
		{
			if(h->getVelocity().y > 0)
			{
				jump = true;
				state = STATE_UP;
			}
		}
		else
		{
			state = STATE_DOWN;
			h->setPositionY(pos.y - 14);
		}
	}
	hero = h;
}
