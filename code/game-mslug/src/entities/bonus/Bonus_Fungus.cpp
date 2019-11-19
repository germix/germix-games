////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Fungus | Bonus hongo
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Fungus.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Bonus_Fungus::NAME = "Fungus";

#define TIME_1	1.8
#define TIME_2	0.06

Bonus_Fungus::Bonus_Fungus(Scene* scene, double x, double y) : Bonus(scene, x, y)
{
	sprite = res.findSpriteSheet("Bonus.Fungus")->getSprite();
	spriteClock.reset(TIME_1);
}
Bonus_Fungus::~Bonus_Fungus()
{
}
void Bonus_Fungus::animate(double dt)
{
	if(onGround)
	{
		if(spriteClock.update(dt))
		{
			spriteFrame++;
			if(spriteFrame == 1)
			{
				spriteClock.reset(TIME_2);
			}
			else if(spriteFrame >= sprite->count())
			{
				spriteFrame = 0;
				spriteClock.reset(TIME_1);
			}
		}
	}
}
void Bonus_Fungus::activate(Hero* hero)
{
	hero->addScore(1000);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 1000));
}
