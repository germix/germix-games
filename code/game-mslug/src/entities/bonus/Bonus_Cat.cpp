////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Cat | Bonus gatito
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Cat.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const int Bonus_Cat::frames1[] = {0};
const int Bonus_Cat::frames2[] = {1,2};
const int Bonus_Cat::frames3[] = {3};
const int Bonus_Cat::frames4[] = {2,1,0,1,2,3,4,5,4,3,2,1};

Bonus_Cat::AnimationStep Bonus_Cat::animationSteps[] =
{
	{	2.0,	(sizeof(frames1)/sizeof(frames1[0])),	frames1,		},
	{	0.1,	(sizeof(frames2)/sizeof(frames2[0])),	frames2,		},
	{	0.8,	(sizeof(frames3)/sizeof(frames3[0])),	frames3,		},
	{	0.1,	(sizeof(frames4)/sizeof(frames4[0])),	frames4,		},
};
const int Bonus_Cat::animationStepsLength = sizeof(animationSteps)/sizeof(animationSteps[0]);

const char* Bonus_Cat::NAME = "Cat";

Bonus_Cat::Bonus_Cat(Scene* scene, double x, double y) : Bonus(scene, x, y)
, animationStepIndex(0)
, animationStepFrame(0)
{
	sprite = res.findSpriteSheet("Bonus.Cat")->getSprite();
	spriteClock.reset(animationSteps[animationStepIndex].delay);
	spriteFrame = animationSteps[animationStepIndex].frames[animationStepFrame];
}
Bonus_Cat::~Bonus_Cat()
{
}
void Bonus_Cat::animate(double dt)
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
void Bonus_Cat::activate(Hero* hero)
{
	hero->addScore(100);
	scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 100));
}


