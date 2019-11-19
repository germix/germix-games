////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Jewel | Bonus joya
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Jewel.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

Bonus_Jewel::Bonus_Jewel(Scene* scene, double x, double y, const char* s) : Bonus(scene, x, y)
{
	sprite = res.findSpriteSheet("Bonus.Jewel")->getSprite(s);
	spriteClock.reset(0.06);
}
Bonus_Jewel::~Bonus_Jewel()
{
}
void Bonus_Jewel::animate(double dt)
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
void Bonus_Jewel::activate(Hero *hero)
{
	hero->addScore(100);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 100));
}
