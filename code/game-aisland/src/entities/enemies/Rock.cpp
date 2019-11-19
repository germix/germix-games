////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Rock
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/Rock.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/hero/HeroBulletAx.h>
#include <src/entities/hero/HeroBulletFireball.h>
#include <src/entities/effects/ScoreEffect.h>
#include <src/entities/effects/SplashEffect.h>

#include <mach/Graphics.h>

Rock::Rock(Scene* s, double x, double y) : Enemy(s, x, y)
, texture(res.findTexture("Rock"))
{
}
Rock::~Rock()
{
}
void Rock::update(double dt)
{
}
void Rock::render(Graphics* gr)
{
	gr->drawTexture(texture, int(pos.x - 8), int(pos.y - 16));
}
void Rock::collides(Entity* e)
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
		
		scene->getHero()->addScore(50, 0);
		scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 50));
		scene->addEntity(new SplashEffect(scene, e->getPosition().x, e->getPosition().y));
	}
}
Rectanglef Rock::getCollisionRectangle() const
{
	if(Debug::disableEnemiesCollision)
		return Rectanglef();
	return Rectanglef(pos.x - 8, pos.y - 16, 16, 16);
}
