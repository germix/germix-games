////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Skull
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/Skull.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/HeroBullet.h>

#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

struct
{
	int x;
	int y;
}deltas[] = 
{
	{	0,		+1	},
	{	0,		0	},
	{	+1,		0	},
	{	0,		0	},
	{	0,		-1	},
	{	0,		0	},
	{	-1,		0	},
	{	0,		0	},
};
#define MAX_DELTAS (sizeof(deltas)/sizeof(deltas[0]))

Skull::Skull(Scene* s, double x, double y) : Enemy(s, x, y)
, alive(true)
, velocity()
, deltaIndex(0)
, sheet(res.findSpriteSheet("Skull"))
, sprite(sheet->getSprite("Idle"))
, spriteIndex(0)
, spriteClock(0.05)
{
}
Skull::~Skull()
{
}
void Skull::update(double dt)
{
	if(alive)
	{
		if(spriteClock.update(dt))
		{
			deltaIndex++;
			if(deltaIndex >= MAX_DELTAS)
				deltaIndex = 0;
			spriteIndex++;
			if(spriteIndex >= sprite->count())
				spriteIndex = 0;
		}
	}
	else
	{
		pos += velocity*dt + (Scene::GRAVITY_ACCELERATION*dt*dt)/2;
		velocity += Scene::GRAVITY_ACCELERATION*dt;
		
		if(pos.y - 22 > scene->getCameraRect().getMaxY())
		{
			removable = true;
		}
	}
}
void Skull::render(Graphics* gr)
{
	if(!alive)
		sprite->render(gr, pos.x, pos.y, 0, 0);
	else
		sprite->render(gr, pos.x + deltas[deltaIndex].x, pos.y + deltas[deltaIndex].y, spriteIndex, 0);
}
void Skull::collides(Entity* e)
{
	if(dynamic_cast<Hero*>(e))
	{
		collideWithHero((Hero*)e);
	}
	else if(dynamic_cast<HeroBullet*>(e))
	{
		alive = false;
		sprite = sheet->getSprite("Dead");
		if(((HeroBullet*)e)->getVelocity().x > 0)
			velocity = Vector2f(+70, -80);
		else
			velocity = Vector2f(-70, -80);
		((HeroBullet*)e)->remove();
		
		Mixer::playChannel(res.findSound("KillEnemy"));
	}
}
Rectanglef Skull::getCollisionRectangle() const
{
	if(!alive)
		return Rectanglef();
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return Rectanglef(pos.x - 6, pos.y - 7, 12, 14);
}
