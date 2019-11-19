////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SideFighter
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/SideFighter.h>
#include <src/entities/hero/Hero.h>
#include <src/sprites/Sprite.h>
#include <src/sprites/SpriteSheet.h>
#include <src/Scene.h>
#include <src/entities/explosions/NormalExplosion.h>
#include <src/entities/enemies/bullets/EnemyBullet.h>

SideFighter::SideFighter(Scene* s, Hero* h, Direction d)
: pos(-100,-100)
, dir(d)
, hero(h)
, scene(s)
, state(STATE_ENTER)
, destroyed(false)
, sprite(null)
, spriteIndex(0)

, spriteForNormal(null)
, spriteForLooping(null)

, health(50)
, canHurt(true)
, hurtTime(0.4)
{
	spriteForLooping = hero->sheet->getSprite("SideFighter.Looping");
	if(dir == Direction_Left)
		spriteForNormal = hero->sheet->getSprite("SideFighter.NormalLeft");
	else
		spriteForNormal = hero->sheet->getSprite("SideFighter.NormalRight");
	
}
SideFighter::~SideFighter()
{
}
Rectanglef SideFighter::rect() const
{
	return sprite->rect(pos);
}
void SideFighter::update(double dt)
{
	if(hurtTime.update(dt))
	{
		canHurt = true;
	}
	//
	// Seleccionar sprite
	//
	switch(state)
	{
		case STATE_NONE:
			sprite = null;
			break;
		case STATE_ENTER:
			sprite = spriteForNormal;
			spriteIndex = 2;
			break;
		case STATE_LEAVE:
			sprite = spriteForNormal;
			spriteIndex = 2;
			break;
		case STATE_ACTIVE:
			if(hero->state != Hero::STATE_LOOPING)
			{
				sprite = spriteForNormal;
				spriteIndex = hero->spriteIndex;
			}
			else
			{
				sprite = spriteForLooping;
				spriteIndex = hero->spriteIndex/4;
			}
			break;
	}
	switch(hero->state)
	{
		default:
			state = STATE_NONE;
			break;
		case Hero::STATE_DESCEND:
			if(state != STATE_NONE)
			{
				state = STATE_LEAVE;
				if(!decrY(dt))
				{
					state = STATE_NONE;
				}
			}
			break;
		case Hero::STATE_NORMAL:
		case Hero::STATE_LOOPING:
		case Hero::STATE_LEAVING:
			switch(state)
			{
				case STATE_NONE:
					state = STATE_ENTER;
					break;
				case STATE_ENTER:
					moveX();
					if(!incrY(dt))
						state = STATE_ACTIVE;
					break;
				case STATE_ACTIVE:
					moveX();
					moveY();
					break;
				default:
					// TODO: Nunca debería pasar
					break;
			}
			break;
		case Hero::STATE_DEAD:
		case Hero::STATE_DYING:
		case Hero::STATE_ASCEND:
		case Hero::STATE_ENTERING:
			// Nada
			break;
	}
}
void SideFighter::render(Graphics* gr)
{
	if(sprite != null)
	{
		sprite->render(gr, pos.x, pos.y, spriteIndex);
	}
}
void SideFighter::checkHit(EnemyBullet* bullet)
{
	if(canHurt && rect().intersects(bullet->rect()))
	{
		health -= bullet->collisioned();
		if(health <= 0)
		{
			health = 0;
			destroyed = true;
			
			scene->addEntity(new NormalExplosion(scene,
					bullet->position().x,
					bullet->position().y,
					null,
					"explosions.sidefighter.hit",
					"explosions.sidefighter.hit"));
		}
	}
}
bool SideFighter::isDestroyed() const
{
	return destroyed;
}
void SideFighter::moveX()
{
	Rectanglef heroRect = hero->rect();
	
	if(dir == Direction_Left)
	{
		pos.x = heroRect.getMinX() - rect().getWidth()/2;
	}
	else if(dir == Direction_Right)
	{
		pos.x = heroRect.getMaxX() + rect().getWidth()/2;
	}
}
void SideFighter::moveY()
{
	pos.y = hero->pos.y;
}
bool SideFighter::incrY(double dt)
{
	pos.y += (350*dt);
	if(pos.y > hero->pos.y)
	{
		pos.y = hero->pos.y;
		return false;
	}
	return true;
}
bool SideFighter::decrY(double dt)
{
	pos.y -= (350*dt);
	if(pos.y < -10)
	{
		return false;
	}
	return true;
}
