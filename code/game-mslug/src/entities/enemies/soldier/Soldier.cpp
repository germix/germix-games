////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Soldier | Soldado
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/soldier/Soldier.h>
#include <src/Debug.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/enemies/soldier/SoldierBomb.h>
#include <src/entities/enemies/soldier/SoldierBullet.h>
#include <src/entities/enemies/soldier/SoldierDeadEffect.h>

#include <mach/Math.h>
#include <mach/Random.h>
#include <mach/Graphics.h>
#include <mach/Rectanglef.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define DIR_LEFT					(-1)
#define DIR_RIGHT					(+1)

#define TIME_IDLE					0.1
#define TIME_WALK					0.056
#define TIME_THROW_BOMB				0.09
#define TIME_ATTACK_SHOOT			0.085
#define TIME_DYING					0.086
#define TIME_LAUGH					0.09
#define TIME_FALLING				0

#define ACTION_TIME					0.5
#define VELOCITY_WALK				98

#define DISTANCE_TO_THROW_BOMB		100

Soldier::Soldier(Scene* scene, double x, double y) : Enemy(scene, x, y)
, state(STATE_NONE)
, sheet(null)
, sprite(null)
, spriteFrame(0)
, spriteClock(0)
, vel()
, accel(0, GRAVITY_CONSTANT*GRAVITY_DOWN)
, onGround(false)
, lastGroundTouchY(0)
, lookX(DIR_LEFT)
, activated(false)
, nextActionTimer(0)
{
	sheet = res.findSpriteSheet("Soldier");
}
Soldier::~Soldier()
{
}
void Soldier::update(double dt)
{
	CollisionInfo ci = scene->moveEntity(this, dt, pos, vel, accel, onGround, MAP_TERRAIN_SOLID|MAP_TERRAIN_TOPDOWN);
	
	//
	// Comprobar toqué con el suelo
	//
	if(ci.flags & COLLISION_FLAG_BOTTOM)
	{
		if(!onGround)
		{
			lastGroundTouchY = (int)pos.y;
			idle();
		}
		vel.y = 0;
		onGround = true;
	}
	//
	// Comprobar caída
	//
	if(((int)pos.y-lastGroundTouchY) > 8)
	{
		if(state == STATE_IDLE || state == STATE_NONE)
		{
			state = STATE_FALLING;
			onGround = false;
			sprite = sheet->getSprite("Falling");
			spriteFrame = 0;
			spriteClock.reset(TIME_FALLING);
		}
	}
	if(!activated)
	{
		if((scene->getCameraRect().getMaxX()+20) > pos.x)
		{
			activated = true;
		}
		return;
	}
	else if(pos.x+20 < scene->getSceneRect().getMinX())
	{
		removable = true;
		return;
	}
	Hero* hero = scene->getHero();
	Vector2f heroPosition = hero->getPosition();
	
	if(hero->isAlive())
	{
		//
		// Comprobar dirección de mirada
		//
		if(heroPosition.x < pos.x)
			lookX = DIR_LEFT;
		else
			lookX = DIR_RIGHT;
	}
	else if(hero->isLoser())
	{
		if(state == STATE_IDLE)
		{
			state = STATE_LAUGH;
			sprite = sheet->getSprite("Laugh");
			spriteFrame = 0;
			spriteClock.reset(TIME_LAUGH);
		}
	}
	switch(state)
	{
		case STATE_NONE:
			if(onGround)
			{
				idle();
			}
			break;
		case STATE_IDLE:
			if(spriteClock.update(dt))
			{
				if(++spriteFrame >= sprite->count()) spriteFrame = 0;
			}
			if(nextActionTimer.update(dt))
			{
				if(!Debug::enemyPassive)
				{
					int r = Random().nextInt(0, 10);
					if(r >= 0 && r <= 3)
						walkBomb();
					else
						shoot();
				}
			}
			break;
		case STATE_WALK_BOMB:
			if(spriteClock.update(dt))
			{
				if(++spriteFrame >= sprite->count()) spriteFrame = 0;
			}
			if(onGround)
			{
				if(heroPosition.getDistanceOf(pos) > DISTANCE_TO_THROW_BOMB)
				{
					vel.x = lookX*VELOCITY_WALK;
				}
				else
				{
					throwBomb();
				}
			}
			break;
		case STATE_THROW_BOMB:
			if(spriteClock.update(dt))
			{
				spriteFrame++;
				if(spriteFrame >= sprite->count())
				{
					idle();
				}
				else if(spriteFrame == 10)
				{
					Point p = sprite->point("Bomb", pos.x, pos.y, spriteFrame, (lookX == DIR_LEFT) ? 0 : Sprite::FLIP_X);
					double bombMaxH = 25;
					double bombPosX = p.x;
					double bombPosY = p.y;
					double bombVelocityX = lookX*DISTANCE_TO_THROW_BOMB;
					double bombVelocityY = GRAVITY_UP*Math::sqrt(2*GRAVITY_CONSTANT*bombMaxH);
					
					scene->addEntity(
							new SoldierBomb(scene,
							bombPosX,
							bombPosY,
							bombVelocityX,
							bombVelocityY));
				}
			}
			break;
		case STATE_ATTACK_SHOOT:
			if(spriteClock.update(dt))
			{
				spriteFrame++;
				if(spriteFrame >= sprite->count())
				{
					idle();
				}
				else if(spriteFrame == 7)
				{
					Point p = sprite->point("Bullet", pos.x, pos.y, spriteFrame, (lookX == DIR_LEFT) ? 0 : Sprite::FLIP_X);
					
					scene->addEntity(new SoldierBullet(scene, p.x, p.y, lookX));
				}
			}
			break;
		case STATE_DYING:
			if(spriteClock.update(dt))
			{
				spriteFrame++;
				if(spriteFrame >= sprite->count())
				{
					destroyed = true;
					removable = true;
				}
			}
			break;
		case STATE_FALLING:
			break;
		case STATE_LAUGH:
			if(spriteClock.update(dt))
			{
				spriteFrame++;
				if(spriteFrame >= sprite->count())
				{
					spriteFrame = 0;
				}
			}
			break;
	}
}
void Soldier::render(Graphics* gr)
{
	if(sprite)
		sprite->render(gr, pos.x, pos.y, spriteFrame, (lookX == DIR_LEFT) ? 0 : Sprite::FLIP_X);
	if(Debug::showEnemyRects)
	{
		gr->drawRect(bounds(), Debug::colorEnemyRects);
	}
}
Rectanglef Soldier::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef Soldier::bounds(double x, double y) const
{
	return Rectanglef(x-10, y-38, 20, 38);
}
void Soldier::knifeHurt(int damage)
{
	die();
}
bool Soldier::isKnifeHurtable() const
{
	return (state != STATE_DYING);
}
void Soldier::hurt(int damage)
{
	die();
}
bool Soldier::isHurtable() const
{
	return (state != STATE_DYING);
}
Rectanglef Soldier::hurtableRect() const
{
	return bounds();
}
void Soldier::die()
{
	scene->getHero()->addScore(50);
	// ...
	vel.x = 0;
	state = STATE_DYING;
	switch(Random().nextInt(1,3))
	{
		case 1: sprite = sheet->getSprite("Dying1"); break;
		case 2: sprite = sheet->getSprite("Dying2"); break;
		case 3: sprite = sheet->getSprite("Dying3"); break;
	}
	spriteFrame = 0;
	spriteClock.reset(TIME_DYING);
	
	Point p = sprite->point("DeadEffect", pos.x, pos.y, spriteFrame, (lookX == DIR_LEFT) ? 0 : Sprite::FLIP_X);
	scene->addEntity(new SoldierDeadEffect(scene, p.x, p.y));
}
void Soldier::idle()
{
	if(state != STATE_IDLE)
	{
		vel.x = 0;
		state = STATE_IDLE;
		sprite = sheet->getSprite("Idle");
		spriteFrame = 0;
		spriteClock.reset(TIME_IDLE);
		nextActionTimer.reset(ACTION_TIME);
	}
}
void Soldier::shoot()
{
	if(state == STATE_IDLE)
	{
		vel.x = 0;
		state = STATE_ATTACK_SHOOT;
		sprite = sheet->getSprite("Shoot");
		spriteFrame = 0;
		spriteClock.reset(TIME_ATTACK_SHOOT);
	}
}
void Soldier::walkBomb()
{
	if(state != STATE_WALK_BOMB)
	{
		state = STATE_WALK_BOMB;
		sprite = sheet->getSprite("Walk");
		spriteFrame = 0;
		spriteClock.reset(TIME_WALK);
	}
}
void Soldier::throwBomb()
{
	if(state == STATE_IDLE || state == STATE_WALK_BOMB)
	{
		vel.x = 0;
		state = STATE_THROW_BOMB;
		sprite = sheet->getSprite("Bomb");
		spriteFrame = 0;
		spriteClock.reset(TIME_THROW_BOMB);
	}
}
bool Soldier::isAlive() const
{
	return (state != STATE_DYING);
}

