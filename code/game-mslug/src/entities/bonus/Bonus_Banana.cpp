////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Banana | Bonus banana
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Banana.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

#include <mach/Random.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Bonus_Banana::NAME = "Banana";

Bonus_Banana::Bonus_Banana(Scene* scene, double x, double y) : Bonus(scene, x, y)
{
	sprite = res.findSpriteSheet("Bonus.Banana")->getSprite();
	if((Random().nextInt(0, 100) & 1) == 0)
		spriteHints |= Sprite::FLIP_X;
}
Bonus_Banana::~Bonus_Banana()
{
}
void Bonus_Banana::animate(double dt)
{
	if(!onGround || (onGround && spriteFrame > 0))
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
void Bonus_Banana::activate(Hero* hero)
{
	hero->addScore(10);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 10));
}
