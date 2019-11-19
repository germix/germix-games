////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Letter | Bonus carta de amor
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Letter.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const char* Bonus_Letter::NAME = "Letter";

const int Bonus_Letter::framesFalling[] = {6,5,4,3,2,1,0,1,2,3,4,5};
const int Bonus_Letter::framesStooping[] = {4,5,6,7,8,9,10};

const int Bonus_Letter::framesFallingLength = sizeof(framesFalling)/sizeof(framesFalling[0]);
const int Bonus_Letter::framesStoopingLength = sizeof(framesStooping)/sizeof(framesStooping[0]);

Bonus_Letter::Bonus_Letter(Scene* scene, double x, double y) : Bonus(scene, x, y)
, state(STATE_FALLING)
, frameIndex(0)
{
	sprite = res.findSpriteSheet("Bonus.Letter")->getSprite();
	spriteFrame = framesFalling[frameIndex];
}
Bonus_Letter::~Bonus_Letter()
{
}
void Bonus_Letter::animate(double dt)
{
	switch(state)
	{
		case STATE_FALLING:
			if(spriteClock.update(dt))
			{
				if(++frameIndex >= framesFallingLength)
				{
					frameIndex = 0;
				}
				if(3 == framesFalling[frameIndex])
				{
					if(onGround)
					{
						state = STATE_STOPPING;
						frameIndex = 0;
					}
				}
				spriteFrame = framesFalling[frameIndex];
			}
			break;
		case STATE_STOPPING:
			if(spriteClock.update(dt))
			{
				if(++frameIndex >= framesStoopingLength)
				{
					spriteFrame = 0;
				}
				else
				{
					spriteFrame = framesFalling[frameIndex];
				}
			}
			break;
		case STATE_NOTHING:
			break;
	}
}
void Bonus_Letter::activate(Hero* hero)
{
	hero->addScore(500);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 500));
}

