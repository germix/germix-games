////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MosqueTowerOperatorDead
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/mosque/MosqueTowerOperatorDead.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define MAX_FALLING_FRAME	12
#define MAX_ONGROUND_FRAME	19

MosqueTowerOperatorDead::MosqueTowerOperatorDead(Scene* scene, double x, double y) : Entity(scene, x, y)
, state(STATE_FALLING)
, vel()
, accel(0, GRAVITY_CONSTANT*GRAVITY_DOWN)
, clock(0.06)
, sprite(null)
, spriteFrame(0)
, blinkingCount(0)
{
	sprite = res.findSpriteSheet("MosqueTowerOperatorDead")->getSprite();
}
MosqueTowerOperatorDead::~MosqueTowerOperatorDead()
{
}
void MosqueTowerOperatorDead::update(double dt)
{
	switch(state)
	{
		case STATE_FALLING:
			{
				if(spriteFrame < MAX_FALLING_FRAME)
				{
					if(clock.update(dt))
						spriteFrame++;
				}
				CollisionInfo ci = scene->moveEntity(this, dt, pos, vel, accel, false, MAP_TERRAIN_SOLID);
				if(ci.flags & COLLISION_FLAG_BOTTOM)
				{
					state = STATE_ONGROUND;
				}
			}
			break;
		case STATE_ONGROUND:
			if(clock.update(dt))
			{
				spriteFrame++;
				if(spriteFrame == MAX_ONGROUND_FRAME)
				{
					state = STATE_BLINKING;
					clock.reset(0.05);
				}
			}
			break;
		case STATE_BLINKING:
			if(clock.update(dt))
			{
				blinkingCount++;
				if(blinkingCount == 16*2)
				{
					removable = true;
				}
			}
			break;
	}
}
void MosqueTowerOperatorDead::render(Graphics* gr)
{
	if((blinkingCount&1) == 0)
		sprite->render(gr, pos.x, pos.y, spriteFrame, 0);
}
Rectanglef MosqueTowerOperatorDead::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef MosqueTowerOperatorDead::bounds(double px, double py) const
{
	return sprite->rectangle(px, py, spriteFrame, 0);
}
