////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Sarubia | Nop-03 Sarubia (Tanque blindado disparador de bomba)
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/sarubia/Sarubia.h>
#include <src/Debug.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/NormalExplosionS.h>
#include <src/entities/effects/NormalExplosionM.h>
#include <src/entities/enemies/sarubia/SarubiaBomb.h>
#include <src/entities/enemies/sarubia/SarubiaBombSmoke.h>

#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

static struct ExplosionDescriptor
{
	char	type;
	int		dx;
	int		dy;
}explosionDescriptors[]=
{
	{ 'S', 20, -10 },
	{ 'M', -30, -70 },
	{ 'M', 25, -60 },
	{ 'S', 5, -50 },
	{ 'M', -15, -20 },
};
#define explosionDescriptors_length			(sizeof(explosionDescriptors)/sizeof(explosionDescriptors[0]))

#define DISTANCE_TO_ACTIVATION				200
#define VELOCITY_DRIVING					40

#define DRIVING_DISTANCE					50
#define TIME_IDLE							0.09
#define TIME_DRIVING						0.08
#define TIME_STOPING						0.05
#define TIME_PREPARING						0.07
#define TIME_SHOOTING						0.06
#define TIME_WRECKED						0.04

Sarubia::Sarubia(Scene* scene, double x, double y) : Enemy(scene, x, y)
, state(STATE_NOTHING)
, onGround(false)
, vel()
, accel(0, GRAVITY_CONSTANT*GRAVITY_DOWN)
, sprite(null)
, spriteFrame(0)
, spriteClock()
, initialX((int)x)
, shootingClock(4)
, healt(100)
, currentExplosion(0)
, explosionClock(0.3)
{
	SpriteSheet* sheet = res.findSpriteSheet("Sarubia");
	SPRITE_IDLE			= sheet->getSprite("Idle");
	SPRITE_DRIVING		= sheet->getSprite("Driving");
	SPRITE_STOPPING		= sheet->getSprite("Stopping");
	SPRITE_PREPARING	= sheet->getSprite("PreparingShoot");
	SPRITE_SHOOTING		= sheet->getSprite("Shooting");
	SPRITE_WRECKED		= sheet->getSprite("Wrecked");

	sprite = SPRITE_IDLE;
}
Sarubia::~Sarubia()
{
}
void Sarubia::update(double dt)
{
	CollisionInfo ci = scene->moveEntity(this, dt, pos, vel, accel, onGround, MAP_TERRAIN_SOLID|MAP_TERRAIN_TOPDOWN);
	
	if(ci.flags & COLLISION_FLAG_BOTTOM)
	{
		vel.y = 0;
		onGround = true;
	}
	switch(state)
	{
		case STATE_NOTHING:
			if(ci.flags & COLLISION_FLAG_BOTTOM)
			{
				Vector2f heroPos = scene->getHero()->getPosition();
				if(pos.x - heroPos.x <= DISTANCE_TO_ACTIVATION)
				{
					state = STATE_DRIVING;
					sprite = SPRITE_DRIVING;
					spriteFrame = 0;
					spriteClock.reset(TIME_DRIVING);
					vel.x = -VELOCITY_DRIVING;
				}
				else if(spriteClock.update(dt))
				{
					spriteFrame = (++spriteFrame)&1;
				}
			}
			else
			{
				spriteFrame = 0;
			}
			break;
		case STATE_IDLE:
			if(shootingClock.update(dt))
			{
				state = STATE_PREPARING;
				sprite = SPRITE_PREPARING;
				spriteFrame = 0;
				spriteClock.reset(TIME_PREPARING);
			}
			else if(spriteClock.update(dt))
			{
				spriteFrame = (++spriteFrame)&1;
			}
			break;
		case STATE_DRIVING:
			if(initialX - pos.x > DRIVING_DISTANCE)
			{
				state = STATE_STOPPING;
				sprite = SPRITE_STOPPING;
				spriteFrame = 0;
				spriteClock.reset(TIME_STOPING);
				vel.x = 0;
			}
			else if(spriteClock.update(dt))
			{
				spriteFrame++;
				if(spriteFrame >= sprite->count())
				{
					spriteFrame = 0;
				}
			}
			break;
		case STATE_STOPPING:
			if(spriteClock.update(dt))
			{
				spriteFrame++;
				if(spriteFrame >= sprite->count())
				{
					state = STATE_IDLE;
					sprite = SPRITE_IDLE;
					spriteFrame = 0;
					spriteClock.reset(TIME_IDLE);
				}
			}
			break;
		case STATE_PREPARING:
			if(spriteClock.update(dt))
			{
				spriteFrame++;
				if(spriteFrame >= sprite->count())
				{
					state = STATE_SHOOTING;
					sprite = SPRITE_SHOOTING;
					spriteFrame = 0;
					spriteClock.reset(TIME_SHOOTING);
				}
			}
			break;
		case STATE_SHOOTING:
			if(spriteClock.update(dt))
			{
				spriteFrame++;
				if(spriteFrame >= sprite->count())
				{
					state = STATE_IDLE;
					sprite = SPRITE_IDLE;
					spriteFrame = 0;
					spriteClock.reset(TIME_IDLE);
				}
				if(spriteFrame == 1)
				{
					Point p = SPRITE_SHOOTING->point("Bomb", pos.x, pos.y, spriteFrame, 0);
					scene->addEntity(new SarubiaBombSmoke(scene, p.x, p.y));
				}
				if(spriteFrame == 4)
				{
					Point p = SPRITE_SHOOTING->point("Bomb", pos.x, pos.y, spriteFrame, 0);
					scene->addEntity(new SarubiaBomb(scene, p.x, p.y));
				}
			}
			break;
		case STATE_WRECKED:
			if(spriteFrame < sprite->count()-1)
			{
				if(spriteClock.update(dt))
				{
					spriteFrame++;
				}
			}
			//
			// Generar explosiones
			//
			if(currentExplosion < explosionDescriptors_length)
			{
				if(explosionClock.update(dt))
				{
					ExplosionDescriptor* ed = &explosionDescriptors[currentExplosion++];
					if(ed->type == 'S')
					{
						scene->addEntity(new NormalExplosionS(scene, pos.x + ed->dx, pos.y + ed->dy));
					}
					else if(ed->type == 'M')
					{
						scene->addEntity(new NormalExplosionM(scene, pos.x + ed->dx, pos.y + ed->dy));
					}
				}
			}
			break;
	}
	if(bounds().getMaxX() < scene->getSceneRect().getMinX())
	{
		removable = true;
	}
}
void Sarubia::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteFrame, 0);
	if(Debug::showEnemyRects)
	{
		gr->drawRect(bounds(), Debug::colorEnemyRects);
		gr->drawRect(hurtableRect(), Debug::colorEnemyRects);
	}
}
Rectanglef Sarubia::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef Sarubia::bounds(double px, double py) const
{
	return sprite->rectangle(px, py, spriteFrame, 0);
}
void Sarubia::hurt(int damage)
{
	if(healt > 0)
	{
		healt -= damage;
		if(healt <= 0)
		{
			scene->getHero()->addScore(200);
			// ...
			state = STATE_WRECKED;
			destroyed = true;
			sprite = SPRITE_WRECKED;
			spriteFrame = 0;
			spriteClock.reset(TIME_WRECKED);
		}
	}
}
bool Sarubia::isHurtable() const
{
	return (state != STATE_WRECKED);
}
Rectanglef Sarubia::hurtableRect() const
{
	if(state == STATE_WRECKED)
	{
		return Rectanglef(pos.x-26, pos.y-64, 44, 64);
	}
	return Rectanglef(pos.x-26, pos.y-78, 44, 78);
}

