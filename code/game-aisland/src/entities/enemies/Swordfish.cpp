////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Swordfish
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/Swordfish.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/HeroBullet.h>

#include <mach/Mixer.h>
#include <mach/Graphics.h>

Swordfish::Swordfish(Scene* s, double x, double y) : Enemy(s, x, y)
, alive(true)
, texture(res.findTexture("Swordfish"))
, velocity(-50, 0)
{
}
Swordfish::~Swordfish()
{
}
void Swordfish::update(double dt)
{
	pos += velocity*dt + (Scene::GRAVITY_ACCELERATION*dt*dt)/2;
	velocity += Scene::GRAVITY_ACCELERATION*dt;

	if(alive)
	{
		if(pos.y-20 > scene->getCameraRect().getMaxY())
		{
			velocity.y = -430;
		}
	}
	else
	{
		if(pos.y-20 > scene->getCameraRect().getMaxY())
		{
			removable = true;
		}
	}
	if(pos.x+64 < scene->getCameraRect().getMinX())
		removable = true;
}
void Swordfish::render(Graphics* gr)
{
	gr->drawTexture(texture, int(pos.x - 32), int(pos.y - 10));
}
void Swordfish::collides(Entity* e)
{
	if(dynamic_cast<Hero*>(e))
	{
		collideWithHero((Hero*)e);
	}
	else if(dynamic_cast<HeroBullet*>(e))
	{
		alive = false;
		texture = res.findTexture("Swordfish.Dead");
		velocity = Vector2f(0, -60);
		((HeroBullet*)e)->remove();
		
		Mixer::playChannel(res.findSound("KillEnemy"));
	}
}
Rectanglef Swordfish::getCollisionRectangle() const
{
	if(!alive)
		return Rectanglef();
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return Rectanglef(pos.x - 28, pos.y - 10, 56, 10);
}
