////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Treasure | Bonus caja de tesoro
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Treasure.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Bonus_Treasure::NAME = "Treasure";

Bonus_Treasure::Bonus_Treasure(Scene* scene, double x, double y) : Bonus(scene, x, y)
{
	sprite = res.findSpriteSheet("Bonus.Treasure")->getSprite();
	spriteClock.reset(0.06);
}
Bonus_Treasure::~Bonus_Treasure()
{
}
void Bonus_Treasure::animate(double dt)
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
void Bonus_Treasure::activate(Hero* hero)
{
	hero->addScore(1000);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 1000));
}

