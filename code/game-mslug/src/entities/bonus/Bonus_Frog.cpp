////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Frog | Bonus rana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Frog.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/ScoreEffect.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

const int Bonus_Frog::frames1[] = {0,1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,0};
const int Bonus_Frog::frames2[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};

Bonus_Frog::AnimationStep Bonus_Frog::animationSteps[] =
{
	{	0.14,	(sizeof(frames1)/sizeof(frames1[0])),	frames1,		},
	{	0.08,	(sizeof(frames2)/sizeof(frames2[0])),	frames2,		},
};
const int Bonus_Frog::animationStepsLength = sizeof(animationSteps)/sizeof(animationSteps[0]);

const char* Bonus_Frog::NAME = "Frog";

Bonus_Frog::Bonus_Frog(Scene* scene, double x, double y) : Bonus(scene, x, y)
, animationStepIndex(0)
, animationStepFrame(0)
{
	sprite = res.findSpriteSheet("Bonus.Frog")->getSprite();
	spriteClock.reset(animationSteps[animationStepIndex].delay);
	spriteFrame = animationSteps[animationStepIndex].frames[animationStepFrame];
}
Bonus_Frog::~Bonus_Frog()
{
}
Rectanglef Bonus_Frog::bounds(double px, double py) const
{
	return sprite->rectangle("Bounds", px, py, spriteFrame, spriteHints);
}
/*
void Bonus_Frog::collide(Entity* other)
{
	if(animationStepIndex == 0)
		Bonus::collide(other);
}
*/
void Bonus_Frog::animate(double dt)
{
	if(onGround)
	{
		if(spriteClock.update(dt))
		{
			if(++animationStepFrame >= animationSteps[animationStepIndex].count)
			{
				animationStepFrame = 0;
				if(++animationStepIndex >= animationStepsLength)
				{
					removable = true;
					return;
				}
				spriteClock.reset(animationSteps[animationStepIndex].delay);
			}
			spriteFrame = animationSteps[animationStepIndex].frames[animationStepFrame];
		}
	}
}
void Bonus_Frog::activate(Hero* hero)
{
	if(animationStepIndex == 1)
	{
		hero->addScore(10);
		scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 10));
	}
	else
	{
		hero->addScore(500);
		scene->addEntity(new ScoreEffect(scene, pos.x, pos.y, 500));
	}
}

