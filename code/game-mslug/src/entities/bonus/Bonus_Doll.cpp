////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Doll | Bonus muñeca
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Doll.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Bonus_Doll::NAME = "Doll";

Bonus_Doll::Bonus_Doll(Scene* scene, double x, double y) : Bonus(scene, x, y)
{
	sprite = res.findSpriteSheet("Bonus.Doll")->getSprite();
	spriteClock.reset(0.08);
}
Bonus_Doll::~Bonus_Doll()
{
}
void Bonus_Doll::animate(double dt)
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
void Bonus_Doll::activate(Hero* hero)
{
	hero->addScore(5000);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 5000));
}

