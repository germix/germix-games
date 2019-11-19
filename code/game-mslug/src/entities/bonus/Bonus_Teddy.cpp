////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Teddy | Bonus osito Teddy
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Teddy.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Bonus_Teddy::NAME = "Teddy";

Bonus_Teddy::Bonus_Teddy(Scene* scene, double x, double y) : Bonus(scene, x, y)
{
	sprite = res.findSpriteSheet("Bonus.Teddy")->getSprite();
	spriteClock.reset(0.1);
}
Bonus_Teddy::~Bonus_Teddy()
{
}
void Bonus_Teddy::animate(double dt)
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
void Bonus_Teddy::activate(Hero* hero)
{
	hero->addScore(5000);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 5000));
}

