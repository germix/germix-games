////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Pig | Bonus Babe, el chanchito valiente! =)
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Pig.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Bonus_Pig::NAME = "Pig";

Bonus_Pig::Bonus_Pig(Scene* scene, double x, double y) : Bonus(scene, x, y)
, state(STATE_FALLING)
{
	sprite = res.findSpriteSheet("Bonus.Pig")->getSprite("Falling");
	spriteClock.reset(0.02);
}
Bonus_Pig::~Bonus_Pig()
{
}
void Bonus_Pig::animate(double dt)
{
	switch(state)
	{
		case STATE_IDLE:
			if(spriteClock.update(dt))
			{
				if(++spriteFrame >= sprite->count())
				{
					spriteFrame = 0;
				}
			}
			break;
		case STATE_FALLING:
			if(spriteClock.update(dt))
			{
				if(++spriteFrame >= sprite->count())
				{
					spriteFrame = 0;
				}
				if(onGround)
				{
					state = STATE_IDLE;
					sprite = res.findSpriteSheet("Bonus.Pig")->getSprite("Idle");
					spriteClock.reset(0.1);
				}
			}
			break;
	}
}
void Bonus_Pig::activate(Hero* hero)
{
	hero->addScore(1000);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 1000));
}

