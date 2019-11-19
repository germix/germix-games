////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Coin | Bonus moneda
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Coin.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Bonus_Coin::NAME = "Coin";

Bonus_Coin::Bonus_Coin(Scene* scene, double x, double y) : Bonus(scene, x, y)
{
	sprite = res.findSpriteSheet("Bonus.Coin")->getSprite();
	spriteClock.reset(0.05);
}
Bonus_Coin::~Bonus_Coin()
{
}
void Bonus_Coin::animate(double dt)
{
	if(spriteClock.update(dt))
	{
		if(++spriteFrame >= sprite->count())
		{
			spriteFrame = 0;
		}
	}
}
void Bonus_Coin::activate(Hero* hero)
{
	hero->addScore(50);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 50));
}

