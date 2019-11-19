////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Bombs | Bonus incrementar la munición de bombas
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Bombs.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/BonusEffect.h>

#include <mach/Mixer.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Bonus_Bombs::NAME = "Bombs";

Bonus_Bombs::Bonus_Bombs(Scene* scene, double x, double y) : Bonus(scene, x, y)
, activated(false)
{
	sprite = res.findSpriteSheet("Bonus.Bombs")->getSprite();
	spriteClock.reset(0.06);
}
Bonus_Bombs::~Bonus_Bombs()
{
}
void Bonus_Bombs::collide(Entity* other)
{
	if(!activated)
	{
		if(dynamic_cast<Hero*>(other))
		{
			activate((Hero*)other);
			activated = true;
		}
	}
}
void Bonus_Bombs::animate(double dt)
{
	if(!activated)
	{
		if(spriteClock.update(dt))
		{
			if(++spriteFrame >= sprite->count()-1)
			{
				spriteFrame = 0;
			}
		}
	}
	else
	{
		if(spriteClock.update(dt))
		{
			removable = true;
		}
	}
}
void Bonus_Bombs::activate(Hero* hero)
{
	hero->addBombs(10);
	Mixer::playChannel(res.findSound("Bonus.Ok"));
	activated = true;
	spriteFrame = sprite->count()-1;
	spriteClock.reset(0.07);

	Rectanglef r = bounds();
	scene->addEntity(new BonusEffect(scene, r.getCenterX(), r.getCenterY()));
}

