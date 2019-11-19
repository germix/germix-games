////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Medal | Bonus medalla
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Medal.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Bonus_Medal::NAME = "Medal";

Bonus_Medal::Bonus_Medal(Scene* scene, double x, double y) : Bonus(scene, x, y)
{
	sprite = res.findSpriteSheet("Bonus.Medal")->getSprite();
	spriteClock.reset(0.09);
}
Bonus_Medal::~Bonus_Medal()
{
}
void Bonus_Medal::animate(double dt)
{
	if(onGround)
	{
		if(spriteClock.update(dt))
		{
			if(++spriteFrame >= sprite->count())
			{
				spriteFrame = 0;
			}
		}
	}
}
void Bonus_Medal::activate(Hero* hero)
{
	hero->addScore(10);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 10));
}


