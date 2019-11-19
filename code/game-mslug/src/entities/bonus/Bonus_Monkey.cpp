////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Monkey | Bonus mono
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Monkey.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

#include <mach/Random.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Bonus_Monkey::NAME = "Monkey";

Bonus_Monkey::Bonus_Monkey(Scene* scene, double x, double y) : Bonus(scene, x, y)
{
	if((Random().nextInt()&1) == 0)
		sprite = res.findSpriteSheet("Bonus.Monkey")->getSprite("1");
	else
		sprite = res.findSpriteSheet("Bonus.Monkey")->getSprite("2");
	
	spriteClock.reset(0.06);
}
Bonus_Monkey::~Bonus_Monkey()
{
}
void Bonus_Monkey::animate(double dt)
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
void Bonus_Monkey::activate(Hero* hero)
{
	hero->addScore(1000);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 1000));
}

