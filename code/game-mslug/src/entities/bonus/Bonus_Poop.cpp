////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Poop | Bonus caquita
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Poop.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Bonus_Poop::NAME = "Poop";

Bonus_Poop::Bonus_Poop(Scene* scene, double x, double y) : Bonus(scene, x, y)
{
	sprite = res.findSpriteSheet("Bonus.Poop")->getSprite();
	spriteClock.reset(0.08);
}
Bonus_Poop::~Bonus_Poop()
{
}
void Bonus_Poop::animate(double dt)
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
void Bonus_Poop::activate(Hero* hero)
{
	hero->addScore(10);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 10));
}