////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Enemy
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/Enemy.h>
#include <src/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>
#include <src/entities/effects/SplashEffect.h>
#include <src/entities/enemies/Rock.h>
#include <src/entities/enemies/Skull.h>
#include <src/entities/enemies/Icicle.h>
#include <src/entities/enemies/WoodFire.h>
#include <src/entities/Egg.h>

#include <mach/Mixer.h>
#include <src/ResourceManager.h>

Enemy::Enemy(Scene* s, double x, double y, const String& ___eggEntity) : Entity(s, x, y), eggEntity(___eggEntity)
{
}
Enemy::~Enemy()
{
}
void Enemy::collideWithHero(Hero* h)
{
	if(h->hasHoneygirl())
	{
		Rectanglef r = h->getCollisionRectangle().intersected(getCollisionRectangle());
		double x = r.getCenterX();
		double y = r.getCenterY();
		removable = true;
		scene->getHero()->addScore(50, 0);
		scene->addEntity(new ScoreEffect(scene, x, y, 50));
		scene->addEntity(new SplashEffect(scene, x, y));
		
		Mixer::playChannel(res.findSound("CollidesWithHoneygirl"));
		return;
	}
	if(h->hasSkate())
	{
		if(h->isOnGround() && !eggEntity.empty())
		{
			scene->addEntity(new Egg(scene, h->getPosition().x, h->getPosition().y, eggEntity));
		}
		removable = true;
		h->releaseSkate(pos);
		return;
	}
	if(dynamic_cast<Rock*>(this))
	{
		h->stumble();
		return;
	}
	if(dynamic_cast<Skull*>(this))
	{
		h->burn();
		return;
	}
	if(dynamic_cast<WoodFire*>(this))
	{
		h->burn();
		return;
	}
	if(dynamic_cast<Icicle*>(this))
	{
		h->freeze();
		removable = true;
		return;
	}
	h->dead();
}
bool Enemy::collideWithHoneygirl(Hero* h)
{
	if(h->hasHoneygirl())
	{
		removable = true;
		scene->getHero()->addScore(50, 0);
		scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 50));
		scene->addEntity(new SplashEffect(scene, h->getPosition().x, h->getPosition().y));
		
		return true;
	}
	return false;
}

