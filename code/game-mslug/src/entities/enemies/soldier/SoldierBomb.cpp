////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SoldierBomb | Bomba del soldado
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/soldier/SoldierBomb.h>
#include <src/Debug.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/enemies/soldier/SoldierBombExplosion.h>

#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

static const int HINTS_TO_LEFT[] =
{
	0,0,0,0,0,0,0,0,
	3,3,3,3,3,3,3,3,
};
static const int HINTS_TO_RIGHT[] =
{
	3,3,3,3,3,3,3,3,
	0,0,0,0,0,0,0,0,
};
static const int INDEXES_TO_LEFT[] =
{
	7,6,5,4,3,2,1,0,
	7,6,5,4,3,2,1,0,
};
static const int INDEXES_TO_RIGHT[] =
{
	0,1,2,3,4,5,6,7,
	0,1,2,3,4,5,6,7,
};
#define HINTS_TO_LEFT_LENGTH		(sizeof(HINTS_TO_LEFT)/sizeof(HINTS_TO_LEFT[0]))
#define HINTS_TO_RIGHT_LENGTH		(sizeof(HINTS_TO_RIGHT)/sizeof(HINTS_TO_RIGHT[0]))
#define INDEXES_TO_LEFT_LENGTH		(sizeof(INDEXES_TO_LEFT)/sizeof(INDEXES_TO_LEFT[0]))
#define INDEXES_TO_RIGHT_LENGTH		(sizeof(INDEXES_TO_RIGHT)/sizeof(INDEXES_TO_RIGHT[0]))

SoldierBomb::SoldierBomb(Scene* scene, double px, double py, double vx, double vy) : EnemyProjectile(scene, px, py)
, vel(vx, vy)
, accel(0,GRAVITY_CONSTANT*GRAVITY_DOWN)
, sprite(null)
, animIndex(0)
, animClock(0.038)
, hints(null)
, hintsLength(0)
, indexes(null)
, indexesLength(0)
{
	if(vel.x < 0)
	{
		hints = HINTS_TO_LEFT;
		hintsLength = HINTS_TO_LEFT_LENGTH;
		indexes = INDEXES_TO_LEFT;
		indexesLength = INDEXES_TO_LEFT_LENGTH;
	}
	else
	{
		hints = HINTS_TO_RIGHT;
		hintsLength = HINTS_TO_RIGHT_LENGTH;
		indexes = INDEXES_TO_RIGHT;
		indexesLength = INDEXES_TO_RIGHT_LENGTH;
	}
	sprite = res.findSpriteSheet("SoldierBomb")->getSprite();
}
SoldierBomb::~SoldierBomb()
{
}
void SoldierBomb::update(double dt)
{
	CollisionInfo ci = scene->moveEntity(this, dt, pos, vel, accel, false, MAP_TERRAIN_SOLID);
	
	if(ci.flags & COLLISION_FLAG_BOTTOM)
	{
		explode();
	}
	else
	{
		if(animClock.update(dt))
		{
			if(++animIndex >= indexesLength)
			{
				animIndex = 0;
			}
		}
	}
}
void SoldierBomb::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, indexes[animIndex], hints[animIndex]);

	if(Debug::showBulletRects)
	{
		gr->drawRect(bounds(), Debug::colorBulletRects);
	}
}
Rectanglef SoldierBomb::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef SoldierBomb::bounds(double px, double py) const
{
	return Rectanglef(px-5, py-5, 10, 10);
}
void SoldierBomb::collide(Entity* other)
{
	if(dynamic_cast<Hero*>(other))
	{
		explode();
	}
}
Rectanglef SoldierBomb::collisionRect() const
{
	return bounds();
}
void SoldierBomb::explode()
{
	removable = true;
	scene->addEntity(new SoldierBombExplosion(scene, pos.x, pos.y));
	if(scene->getHero()->bounds().intersects(Rectanglef(pos.x-10, pos.y-10, 20, 20)))
	{
		scene->getHero()->hurt();
	}
}
