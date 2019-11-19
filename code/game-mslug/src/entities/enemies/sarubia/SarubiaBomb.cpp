////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SarubiaBomb | Bomba disparada por Sarubia
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/sarubia/SarubiaBomb.h>
#include <src/Debug.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/NormalExplosionS.h>

#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

static const int INDEXES_NOTHING[] = {0,1,2,3,4,5,6,7};
static const int INDEXES_BOUNCE[]  = {8,9,10,11,12};
static const int INDEXES_ROLLING[] = {13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33};

#define INDEXES_NOTHING_LENGTH		(sizeof(INDEXES_NOTHING)/sizeof(INDEXES_NOTHING[0]))
#define INDEXES_BOUNCE_LENGTH		(sizeof(INDEXES_BOUNCE)/sizeof(INDEXES_BOUNCE[0]))
#define INDEXES_ROLLING_LENGTH		(sizeof(INDEXES_ROLLING)/sizeof(INDEXES_ROLLING[0]))

#define TIME_NOTHING				0.03
#define TIME_BOUNCE					0.05
#define TIME_ROLLING				0.07

SarubiaBomb::SarubiaBomb(Scene* scene, double x, double y) : EnemyProjectile(scene, x, y)
, state(STATE_NOTHING)
, vel()
, accel(0, GRAVITY_CONSTANT*GRAVITY_DOWN)
, onGround(false)
, animIndex(0)
, sprite(null)
, spriteFrame(0)
, spriteClock(TIME_NOTHING)
{
	sprite = res.findSpriteSheet("SarubiaBomb")->getSprite();
}
SarubiaBomb::~SarubiaBomb()
{
}
void SarubiaBomb::update(double dt)
{
	CollisionInfo ci = scene->moveEntity(this, dt, pos, vel, accel, onGround, MAP_TERRAIN_SOLID);
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
				state = STATE_BOUNCE;
				animIndex = 0;
				spriteFrame = INDEXES_BOUNCE[animIndex];
				spriteClock.reset(TIME_BOUNCE);
			}
			else if(animIndex < INDEXES_NOTHING_LENGTH)
			{
				if(spriteClock.update(dt))
				{
					spriteFrame = INDEXES_NOTHING[animIndex++];
				}
			}
			break;
		case STATE_BOUNCE:
			if(spriteClock.update(dt))
			{
				if(++animIndex >= INDEXES_BOUNCE_LENGTH)
				{
					vel.x = -50;
					state = STATE_ROLLING;
					animIndex = 0;
					spriteFrame = INDEXES_ROLLING[animIndex];
					spriteClock.reset(TIME_ROLLING);
				}
				else
				{
					spriteFrame = INDEXES_BOUNCE[animIndex];
				}
			}
			break;
		case STATE_ROLLING:
			if(scene->getCameraRect().excluded(bounds()))
			{
				removable = true;
			}
			else if(spriteClock.update(dt))
			{
				if(++animIndex >= INDEXES_ROLLING_LENGTH)
				{
					animIndex = 0;
				}
				spriteFrame = INDEXES_ROLLING[animIndex];
			}
			break;
	}
}
void SarubiaBomb::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteFrame, 0);
	if(Debug::showBulletRects)
	{
		gr->drawRect(bounds(), Debug::colorBulletRects);
	}
}
Rectanglef SarubiaBomb::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef SarubiaBomb::bounds(double px, double py) const
{
	return Rectanglef(px - 7, py - 14, 14, 14);
}
void SarubiaBomb::collide(Entity* other)
{
	if(dynamic_cast<Hero*>(other))
	{
		removable = true;
		((Hero*)other)->hurt();
		scene->addEntity(new NormalExplosionS(scene, pos.x, pos.y-14));
	}
}
Rectanglef SarubiaBomb::collisionRect() const
{
	return bounds();
}

