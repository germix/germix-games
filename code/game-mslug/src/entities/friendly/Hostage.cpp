////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Hostage | Rehén
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/friendly/Hostage.h>
#include <src/Debug.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/scene/EntityParameters.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/bonus/Bonus.h>
#include <src/entities/bonus/BonusFactory.h>

#include <mach/Mixer.h>
#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define TIME_SALUTE			0.06
#define TIME_UNTYING		0.08
#define TIME_GIVING_BONUS	0.06

#define DROP_POINT_X		20
#define DROP_POINT_Y		20

#define WALK_DISTANCE		100
#define WALK_VELOCITY		40
#define FLEEING_VELOCITY	100

Hostage::Hostage(Scene* scene, double x, double y, const char* bonus) : Entity(scene, x, y)
, state(STATE_CAPTURED)
, vel()
, accel(0, GRAVITY_CONSTANT*GRAVITY_DOWN)
, lookX(-1)
, onGround(false)
, sheet(null)
, sprite(null)
, spriteFrame(0)
, spriteClock(0.08)
, walkTo(0)
, active(false)
, droppableBonus(bonus)
{
	sheet = res.findSpriteSheet("Hostage");
	sprite = sheet->getSprite("Captured");
}
Hostage::~Hostage()
{
}
void Hostage::update(double dt)
{
	if(!active)
	{
		if(scene->getCameraRect().intersects(bounds()))
		{
			active = true;
		}
		if(!active)
			return;
	}
	CollisionInfo ci = scene->moveEntity(this, dt, pos, vel, accel, onGround, MAP_TERRAIN_SOLID|MAP_TERRAIN_TOPDOWN);
	
	onGround = (ci.flags & COLLISION_FLAG_BOTTOM) != 0;
	if(!onGround)
		return;
	switch(state)
	{
		case STATE_CAPTURED:
			if(spriteClock.update(dt))
			{
				if(++spriteFrame >= sprite->count())
				{
					spriteFrame = 0;
				}
			}
			break;
		case STATE_UNTYING:
			if(spriteClock.update(dt))
			{
				if(++spriteFrame >= sprite->count())
				{
					state = STATE_RELEASED;
					walkTo = (int)(pos.x-WALK_DISTANCE/2);
					sprite = sheet->getSprite("Walking");
					spriteFrame = 0;
				}
			}
			break;
		case STATE_RELEASED:
			if(spriteClock.update(dt))
			{
				if(++spriteFrame >= sprite->count())
				{
					spriteFrame = 0;
				}
			}
			if(lookX == -1)
			{
				vel.x = (-WALK_VELOCITY);
				if(pos.x < walkTo)
				{
					lookX = +1;
					walkTo += WALK_DISTANCE;
				}
			}
			else if(lookX == +1)
			{
				vel.x = (+WALK_VELOCITY);
				if(pos.x > walkTo)
				{
					lookX = -1;
					walkTo -= WALK_DISTANCE;
				}
			}
			break;
		case STATE_GIVING_BONUS:
			if(spriteClock.update(dt))
			{
				if(++spriteFrame >= sprite->count())
				{
					state = STATE_SALUTE;
					sprite = sheet->getSprite("Salute");
					spriteFrame = 0;
					spriteClock.reset(TIME_SALUTE);
					
					//
					// Saludar según la posición del jugador
					//
					Vector2f playerPos = scene->getHero()->getPosition();
					
					if(playerPos.x < pos.x)
						lookX = -1;
					else if(playerPos.x > pos.x)
						lookX = +1;
				}
				else
				{
					if(spriteFrame == sprite->count()-2)
					{
						scene->addEntity(BonusFactory::create(scene, pos.x-DROP_POINT_X, pos.y-DROP_POINT_Y, droppableBonus.c_str()));
					}
				}
			}
			break;
		case STATE_SALUTE:
			if(spriteClock.update(dt))
			{
				if(++spriteFrame >= sprite->count())
				{
					state = STATE_FLEEING;
					//
					// Huir hacia la izquierda
					//
					lookX = -1;
					vel.x = (-FLEEING_VELOCITY);
					// ...
					sprite = sheet->getSprite("Fleeing");
					spriteFrame = 0;
				}
			}
			break;
		case STATE_FLEEING:
			if(spriteClock.update(dt))
			{
				if(++spriteFrame >= sprite->count())
				{
					spriteFrame = 0;
				}
			}
			break;
	}
	//
	// Si está fuera de la cámara, removerlo
	//
//	if(scene->getCameraRect().excluded(bounds()))
	if(scene->getCameraRect().getMinX() > bounds().getMaxX())
	{
		removable = true;
	}
}
void Hostage::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteFrame, (lookX == 1) ? Sprite::FLIP_X : 0);
	if(Debug::showFriendlyRects)
	{
		gr->drawRect(bounds(), Debug::colorFriendlyRects);
	}
}
Rectanglef Hostage::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef Hostage::bounds(double px, double py) const
{
	return sprite->rectangle(px, py, spriteFrame, (lookX == 1) ? Sprite::FLIP_X : 0);
}
void Hostage::knifeHurt(int damage)
{
	release();
}
bool Hostage::isKnifeHurtable() const
{
	return (state == STATE_CAPTURED);
}
void Hostage::hurt(int damage)
{
	release();
}
bool Hostage::isHurtable() const
{
	return (state == STATE_CAPTURED);
}
Rectanglef Hostage::hurtableRect() const
{
	return bounds();
}
void Hostage::collide(Entity* other)
{
	if((state == STATE_RELEASED) && (null != dynamic_cast<Hero*>(other)))
	{
		vel.x = 0;
		lookX = -1;	// Siempre mira hacia la izquierda
		state = STATE_GIVING_BONUS;
		sprite = sheet->getSprite("Bonus");
		spriteFrame = 0;
		spriteClock.reset(TIME_GIVING_BONUS);
		// ...
		Mixer::playChannel(res.findSound("ThankYou"));
		((Hero*)other)->addHostage();
	}
}
Rectanglef Hostage::collisionRect() const
{
	if(state == STATE_RELEASED)
	{
		return sprite->rectangle(pos.x, pos.y, spriteFrame, (lookX == 1) ? Sprite::FLIP_X : 0);
	}
	return Rectanglef();
}
void Hostage::release()
{
	if(state == STATE_CAPTURED)
	{
		scene->getHero()->addScore(100);
		// ...
		state = STATE_UNTYING;
		sprite =  sheet->getSprite("Untying");
		spriteFrame = 0;
		spriteClock.reset(TIME_UNTYING);
	}
}
