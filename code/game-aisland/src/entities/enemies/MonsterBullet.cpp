////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MonsterBullet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/MonsterBullet.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>

#include <gamelib-sprites/Sprite.h>

MonsterBullet::MonsterBullet(Scene* s, double x, double y, Sprite* spr) : Enemy(s, x, y)
, sprite(spr)
, velocity(-200, -160)
{
}
MonsterBullet::~MonsterBullet()
{
}
void MonsterBullet::update(double dt)
{
	pos += velocity*dt + (Scene::GRAVITY_ACCELERATION*dt*dt)/2;
	
	velocity += Scene::GRAVITY_ACCELERATION*dt;
	
	if(!bounds().intersects(scene->getCameraRect()))
	{
		removable = true;
	}
}
void MonsterBullet::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, 1, 0);
}
void MonsterBullet::collides(Entity* e)
{
	if(dynamic_cast<Hero*>(e))
	{
		removable = true;
		collideWithHero((Hero*)e);
	}
}
Rectanglef MonsterBullet::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef MonsterBullet::bounds(double px, double py) const
{
	return Rectanglef(px - 5, py - 5, 10, 10);
}
