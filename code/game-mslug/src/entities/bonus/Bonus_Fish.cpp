////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Fish | Bonus pescado
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Fish.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Bonus_Fish::NAME = "Fish";

Bonus_Fish::Bonus_Fish(Scene* scene, double x, double y) : Bonus(scene, x, y)
{
	sprite = res.findSpriteSheet("Bonus.Fish")->getSprite();
	spriteClock.reset(0.09);
}
Bonus_Fish::~Bonus_Fish()
{
}
void Bonus_Fish::animate(double dt)
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
void Bonus_Fish::activate(Hero* hero)
{
	hero->addScore(500);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 500));
}

