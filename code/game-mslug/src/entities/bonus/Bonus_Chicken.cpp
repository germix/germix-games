////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Chicken | Bonus pollo al horno
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Chicken.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const int Bonus_Chicken::frames1[] = {0,1,2,3,4,5,0,1,2,3,4,5,0,1,2,3,4,5,0,1,2,3,4,5,};
const int Bonus_Chicken::frames2[] = {6,7,8,9,8,7,6,7,8,9,8,7,6,7,8,9,8,7,6,};

Bonus_Chicken::AnimationStep Bonus_Chicken::animationSteps[] =
{
	{	0.07,	(sizeof(frames1)/sizeof(frames1[0])),	frames1,		},
	{	0.03,	(sizeof(frames2)/sizeof(frames2[0])),	frames2,		},
};
const int Bonus_Chicken::animationStepsLength = sizeof(animationSteps)/sizeof(animationSteps[0]);

const char* Bonus_Chicken::NAME = "Chicken";

Bonus_Chicken::Bonus_Chicken(Scene* scene, double x, double y) : Bonus(scene, x, y)
, animationStepIndex(0)
, animationStepFrame(0)
{
	sprite = res.findSpriteSheet("Bonus.Chicken")->getSprite();
	spriteClock.reset(animationSteps[animationStepIndex].delay);
	spriteFrame = animationSteps[animationStepIndex].frames[animationStepFrame];
}
Bonus_Chicken::~Bonus_Chicken()
{
}
void Bonus_Chicken::animate(double dt)
{
	if(onGround)
	{
		if(spriteClock.update(dt))
		{
			if(++animationStepFrame >= animationSteps[animationStepIndex].count)
			{
				animationStepFrame = 0;
				if(++animationStepIndex >= animationStepsLength)
					animationStepIndex = 0;
				
				spriteClock.reset(animationSteps[animationStepIndex].delay);
			}
			spriteFrame = animationSteps[animationStepIndex].frames[animationStepFrame];
		}
	}
}
void Bonus_Chicken::activate(Hero* hero)
{
	hero->addScore(1000);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 1000));
}

