////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RockBall
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/RockBall.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/HeroBulletAx.h>
#include <src/entities/hero/HeroBulletFireball.h>
#include <src/entities/effects/ScoreEffect.h>
#include <src/entities/effects/SplashEffect.h>

#include <mach/Graphics.h>

#define VELOCITY_X			50
#define VELOCITY_REBOUND	78

RockBall::RockBall(Scene* s, double x, double y) : Enemy(s, x, y)
, active(false)
, texture(res.findTexture("RockBall"))
, velocity(-VELOCITY_X, 0)
{
}
RockBall::~RockBall()
{
}
void RockBall::update(double dt)
{
	if(!active)
	{
		if(!scene->getCameraRect().intersects(bounds()))
			return;
		active = true;
	}
	Vector2f oldPosition = pos;
	Vector2f oldVelocity = velocity;
	
	pos += velocity*dt + (Scene::GRAVITY_ACCELERATION*dt*dt)/2;
	velocity += Scene::GRAVITY_ACCELERATION*dt;
	
	unsigned int cflags = scene->checkCollision(
			this,
			pos,
			velocity,
			oldPosition,
			oldVelocity,
			MAP_TERRAIN_SOLID);
	
	if(0 != (cflags & COLLISION_FLAG_LEFT))
	{
		velocity.x = VELOCITY_X;
	}
	if(0 != (cflags & COLLISION_FLAG_RIGHT))
	{
		velocity.x = -VELOCITY_X;
	}
	if(0 != (cflags & COLLISION_FLAG_BOTTOM))
	{
		velocity.y = -VELOCITY_REBOUND;
	}
	if(!scene->getCameraRect().intersects(bounds()))
	{
		removable = true;
	}
}
void RockBall::render(Graphics* gr)
{
	gr->drawTexture(texture, int(pos.x - 12), int(pos.y - 22));
}
void RockBall::collides(Entity* e)
{
	if(dynamic_cast<Hero*>(e))
	{
		collideWithHero((Hero*)e);
	}
	else if(dynamic_cast<HeroBulletAx*>(e))
	{
		((HeroBulletAx*)e)->stop();
	}
	else if(dynamic_cast<HeroBulletFireball*>(e))
	{
		removable = true;
		((HeroBulletFireball*)e)->remove();

		scene->getHero()->addScore(100, 0);
		scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 100));
		scene->addEntity(new SplashEffect(scene, e->getPosition().x, e->getPosition().y));
	}
}
Rectanglef RockBall::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef RockBall::bounds(double px, double py) const
{
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return Rectanglef(px - 9, py - 19, 18, 19);
}
Rectanglef RockBall::getCollisionRectangle() const
{
	return bounds();
}
